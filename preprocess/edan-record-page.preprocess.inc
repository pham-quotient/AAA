<?php

/**
 * Implements hook_preprocess_page().
 */
function si_baseline_preprocess_edan_record_page(&$variables) {
	$dest = isset($_GET['destination']) ? $_GET['destination'] : '';
	$variables['si_header'] = $variables['back_link'] = $variables['search_form'] = '';
	if (!empty($dest)) {
		$url = drupal_parse_url($dest);
		//dpm($url);
		if (isset($url['query']['objectID'])) {
			$objectID = $url['query']['objectID'];
			$si_ogmt = variable_get('si_ogmt_view', array());
			if (isset($si_ogmt['si_header'])) {
				list($name, $display) = explode(':', $si_ogmt['si_header']);
				$variables['si_header'] = views_embed_view($name, $display, $objectID);
			}
		}
		$variables['back_link'] = l(t('Return to Previous Page'), $url['path'], array(
															'query' => $url['query'],
															'fragment' => $url['fragment'],
															'absolute' => TRUE,
															'attributes' => array(
																'class' => array('button', 'button-large')
															)));
	}

	if (empty($variables['si_header'])) {
		$nid = variable_get('si_edan_theme', '');
		if ($nid) {
			$node = node_load($nid);
			$build = node_view($node, 'teaser');
			$variables['si_header'] = drupal_render($build);
		}
	}


//	$variables['breadcrumb'] = '';
//	$links = variable_get('si_ogmt_breadcrumbs', array());
//	if (!empty($links)) {
//		$crumbs = array();
//		$crumbs[] =  l(t('Home'), '<front>');
//		foreach($links as $link => $text) {
//			$crumbs[] = l(t($text), $link);
//		}
//		$variables['breadcrumb'] = theme('breadcrumb', array('breadcrumb' => $crumbs));
//	}

	$edan = variable_get('edan_search', array());
	$edan_search_link = isset($edan['menu_results_page']) ? $edan['menu_results_page'] : '';
	$docs = $variables['docs'];
	$media  = $slideshow = array();
	foreach ($docs as $i => $doc) {
		$items = $attributes = array();
		$attributes['class'][] = 'edan-search-result';
		$attributes['class'][] = isset($doc['flags']['in_list']) && $doc['flags']['in_list'] === TRUE ? ' in-list' : '';
		$attributes['class'][] = empty($doc['content']['media']) ? '' : 'has-media';
		$attributes['class'] = array_filter($attributes['class']);
		$attributes['id'] = $doc['content']['descriptiveNonRepeating']['record_ID'];
		$variables['docs'][$i]['row_attributes'] = $attributes;

			if(array_key_exists('indexedStructured', $doc['content'])) {
			// create a template for the array we're expecting:
			$structuredIndexTemplate = array(
				'geoLocation' => array(
					0 => array(
						'points' => array(
							'point' => array (
								'latitude' => array(
									'content'
								),
								'longitude' => array(
									'content'
								)
							)
						)
					)
				)
			);
			$structuredIndex = array_merge($structuredIndexTemplate, $doc['content']['indexedStructured']);
			$latitude = isset($structuredIndex['geoLocation'][0]['points']['point']['latitude']['content'])
				? $structuredIndex['geoLocation'][0]['points']['point']['latitude']['content']
				: '';
			$longitude = isset($structuredIndex['geoLocation'][0]['points']['point']['longitude']['content'])
				? $structuredIndex['geoLocation'][0]['points']['point']['longitude']['content']
				: '';
			if(strlen($latitude) > 0 || strlen($longitude) > 0) {
				$variable['docs'][$key]['content']['freetext']['geoLocation_0'] = array(
					array(
						'label' => t('Geographic Location'),
						'content' => $latitude . ', ' . $longitude
					)
				);
			}
		}

		foreach ($doc['content']['freetext'] as $field => $vals) {
			switch($field) {
				case 'setName':
					foreach ($vals as $key => $value) {
						$items[$field][$key] = array(
							'label' => t($value['label']),
							'content' => empty($edan_search_link) ? t($value['content']) : l(t($value['content']), $edan_search_link, array('absolute' => TRUE, 'html' => TRUE, 'query' => array('fq' => 'set_name:"'. $value['content'] .'"')))
						);
					}
				break;
				default:
					foreach ($vals as $key => $value) {
						$items[$field][$key] = array(
							'label' => t($value['label']),
							'content' =>  t($value['content'])
						);
					}
				break;
			}
		}
		$variables['docs'][$i]['content']['freetext'] = $items;
		if ($doc['content']['descriptiveNonRepeating']['online_media']['mediaCount'] >= 1) {
			$images = array();
			foreach($doc['content']['descriptiveNonRepeating']['online_media']['media'] as $asset) {
				$asset['attributes']['class'] = array(
					'thumbnail'
				);

				$status = FALSE;
				$response = isUrlExists($asset['content']);
				if ($response['status']) {
						$status = $colorbox = TRUE;
						$attributes = array();
						foreach($response['header'] as $header) {
							$header = trim($header);
							if ($header == 'X-Frame-Options: SAMEORIGIN') {
								$colorbox = FALSE;
							}
						}
				}
				if ($status) {
					switch ($asset['type']) {
						case 'Images':
							$newAsset = _process_image($asset, $colorbox);
							$newAsset['altText'] = t('Image for @title', array('@title' => $doc['#title_plain']));

							$images[] = array_merge($asset, $newAsset);
						break;
						case 'URL':
								if (preg_match('/.+google\.com\/maps.+/', $asset['content'])) {
									preg_match('/-?([1-8]?[0-9]\.{1}\d{1,6}|90\.{1}0{1,6}),-?([1]?[1-7]?[0-9]\.{1}\d{1,6}|180\.{1}0{1,6})/', $asset['content'], $matches);
									if (!empty($matches)) {
										$location = current($matches);
										$asset['content'] = 'https://www.google.com/maps/embed/v1/place?key=AIzaSyDe_paOqwgI1s5R1hyD-FmpjkMSD-zBlSQ&q='. $location .'&zoom=13';
									}
									else {
										$asset = array();
									}
								}
								$media[$asset['type']][] = $asset;
						break;
						default:

							$mimetype = trim(file_get_mimetype($asset['content']));

					  $mime_names = array(
					    'application/msword' => t('Microsoft Office document'),
					    'application/vnd.ms-excel' => t('Office spreadsheet'),
					    'application/vnd.ms-powerpoint' => t('Office presentation'),
					    'application/pdf' => t('PDF'),
					    'video/quicktime' => t('Movie'),
					    'audio/mpeg' => t('Audio'),
					    'audio/wav' => t('Audio'),
					    'image/jpeg' => t('Image'),
					    'image/png' => t('Image'),
					    'image/gif' => t('Image'),
					    'application/zip' => t('Package'),
					    'text/html' => t('Website'),
					    'text/plain' => t('Plain text'),
					    'application/octet-stream' => t('Binary Data'),
					  );
						 $download = array(
    				'application/msword',
				    'application/vnd.ms-excel' ,
				    'application/vnd.ms-powerpoint',
				    'application/zip',
				  	);

						 $link = array(
				    'application/pdf',
				    'text/html',
				    'text/plain',
				    //'application/octet-stream' => t('Binary Data'),
				  	);
						 $imageTypes = array(
				    'image/jpeg',
				    'image/png',
				    'image/gif',
				  	);
				  	$mimename = !empty($mime_names[$mimetype]) ? $mime_names[$mimetype] : t('File');
				  	if (in_array($mimetype, $imageTypes)) {
								$newAsset = _process_image($asset, $colorbox);
								$images[] = array_merge($newAsset, $asset);
								$asset = array();
							}

						 if(isset($download[$mimetype]) || isset($link[$mimetype]) || $mimename == t('PDF')) {
						 	$asset['type'] = isset($download[$mimetype]) ? 'mediaDownload' : 'mediaLink';
						 	$colorbox = isset($download[$mimetype]) ? FALSE : TRUE;

						 	// $file = new stdClass();
						 	// $file->filemime = $mimetype;
						 	// $asset['thumbnail'] = theme('file_icon', array(
    				// 	'file' => $file,
    				// 	'icon_directory' => NULL,
    				// 	'alt' => $mimename,
  						// ));
  						$newAsset = _process_image($asset, $colorbox);
						  $newAsset['attributes']['type'] = $mimetype;
						  $newAsset['title'] = t('Digital Content (@mimename )', array('@mimename' => $mimename));
						  $asset = array_merge($newAsset, $asset);
						 }
						 else {
						 	$asset['title'] = t('Digital Content for @title)', array('@title' => $doc['#title_plain']));
						 }
						 $asset['mimetype'] = $mimename;
						 //$asset['type'] = $asset['type'] == 'slideshowXML' ? $asset['type'] : 'other';
						 if (!empty($asset)) {
						 	$media[$asset['type']][] = $asset;
						 }
						break;
					}
				}

			}
			if (!empty($images)) {
				$media['Images'] = $images;
			}
	//		$i = 0;
			if (isset($media['Images']) && count($media['Images']) > 1) {
				$slides = array();
				foreach ($media['Images'] as $delta => $asset) {
					$j = $delta + 1;
					$media['Images'][$delta]['altText'] = t('Image !num for @title.', array('!num' => $j, '@title' => $doc['#title_plain']));
				}
	 			if (count($media['Images']) > 1) {
	 				$media['slideshow'][]['slides'] = $media['Images'];
	 				unset($media['Images']);
	 			}
			}

			if (isset($media['slideshowXML'])) {
				$slides = $data = array();
				$caption = '';
				foreach ($media['slideshowXML'] as $slide) {
					$xml = simplexml_load_file($slide['content']);
					//dpm($xml);
					$j = 0;
					foreach($xml as $delta => $item) {
						$response = isUrlExists($item->NAME);
						//$test = $item=>NAMEFS;
						if ($response['status']) {
							$j++;
							$caption = isset($item->caption) && !empty($item->caption) ? (string) $item->caption : $caption;
							$colorbox = TRUE;
							$attributes = array();
							$attributes['class'][] = 'collection-image';
							foreach($response['header'] as $header) {
								$header = trim($header);
								if ($header == 'X-Frame-Options: SAMEORIGIN') {
									$colorbox = FALSE;
								}
							}
							$newAsset = _process_image(array('content' => $item->NAME), $colorbox);
							$newAsset['altText'] = t('Image !num for @title.', array('!num' => $j, '@title' => $doc['#title_plain']));
							$slides['slides'][$j] = $newAsset;
						}
					}
					$slides['caption'] = $caption;
					unset($media['slideshowXML']);
					$media['slideshow'][] = $slides;
				}
			}
		}
		$variables['docs'][$i]['content']['media'] = $media;
	}
	if (variable_get('si_edan_incl', FALSE)) {
		$variables['search_form'] = drupal_get_form('edan_search_search_form');
	}

}


function _process_image($asset, $colorbox) {
	$item = array();
	$edan_image = variable_get('si_edan_image', array());
	$item['content'] = $asset['content'];
	$item['thumbnail'] = isset($asset['thumbnail']) ? $asset['thumbnail'] : '';
	$link = drupal_parse_url($asset['content']);
	$parsed = parse_url($link['path']);

	if ($colorbox) {
		$attributes['class'][] = 'colorbox-load';
		$link['query']['iframe'] = 'true';
		$link['query']['width'] = '85%';
		$link['query']['height'] = '85%';

	}

	if ($parsed['host'] === 'ids.si.edu' || isset($asset['idsId'])) {
		$idsID = isset($asset['idsId']) ? $asset['idsId'] : $asset['content'];

		if (isset($edan_image['ids'])) {
			$query = $link['query'];
			$query['id'] = $idsID;
			$query['max'] = isset($edan_image['medium']) ? $edan_image['medium'] : 600;
			$item['content'] = url($edan_image['ids'], array('query' => $query));
			$query['max'] = isset($edan_image['thumb']) ? $edan_image['thumb'] : 200;
			$item['thumbnail'] = url($edan_image['ids'], array('query' => $query));
		}
		$link['query']['max'] = isset($edan_image['max_width']) ? $edan_image['max_width'] : 980;
		if (isset($edan_image['dynamic'])) {
			$link['path'] = $edan_image['dynamic'];
			$link['query']['id'] = $idsID;
			$link['path'] = url($link['path'], array('query' => $link['query'])) . '&container.fullpage';
			$link['query'] = array();
		}
	}

	else {
		$attributes['target'] = '_blank';
	}
	$item['link'] = array(
	'path' => $link['path'],
	'options' => array(
		'query' => $link['query'],
		'absolute' => TRUE,
		'html' => TRUE,
		'attributes' => $attributes
		)
	);
	// if (isset($link['query'])) {

	// }

	return $item;
}


function _media_theme($assets) {
	$items = $data = array();
	$out = '';
	$mediaFloat = TRUE;

	$i = 0;
	foreach($assets as $type => $asset) {
		$out .= '<div class="media-container media-'. strtolower(drupal_clean_css_identifier($type)) .'">';
		foreach ($asset as $key => $media) {
			$out .= '<div class="media">';
			switch ($type) {
				case 'Images':
					$image = isset($media['altText']) ? '<img src="'. $media['content'] .'" alt="'. $media['altText'] .'" />' : '<img src="'. $media['content'] .'" alt="thumbnail" />';
					$out .= l($image, $media['link']['path'], $media['link']['options']);
				break;
				case 'slideshow':
					$mediaFloat = FALSE;
					$slides = $thumbnails = array();
					foreach ($media['slides'] as $j => $slide) {
						$image = isset($media['altText']) ? '<img src="'. $slide['content'] .'" alt="'. $slide['altText'] .'" />' : '<img src="'. $slide['content'] .'" alt="Image for slide '. $j .'" />';
						$thumb_image = '<img src="'. $slide['thumbnail'] .'" class="thumbnail" alt="tumbnail for slide '. $j .'" />';


						$content = '<div class="panel" role="tabpanel" aria-labelledby="tab'. $j .'">';
						$content .= l($image, $slide['link']['path'], $slide['link']['options']);
						$content .= '</div>';
						$slides[$j]['slide'] = $content;
						$thumbnails[$j]['slide'] = $thumb_image;
					}
					$out .= isset($media['caption']) ? '<div class="flex-preface">'. $media['caption']  .'</div>': '';
	//				dpm($media);
	//				$attributes = array('class' => array('slides'));
					$settings = array(
						'attributes' => array(
							'class' => array('slides')
						),
						'optionset' => 'default',
						'type' => 'ul'
					);
					dpm($slides);
					$out .= '<div id="flexslider-'. $key .'" class="flexslider slideshow">';
					$out .= theme('flexslider_list', array('items' => $slides, 'settings' => $settings));
					$out .= '</div>';
					$out	.= '	<div id="navigation-'. $key .'" class="flexslider flex-custom-nav">';
					$out .= theme('flexslider_list', array('items' => $thumbnails, 'settings' => $settings));
					$out .= '</div>';
					$optionset = flexslider_optionset_load('collections');
					$optionset->options['sync'] = '#navigation-'. $key;
					$navset = flexslider_optionset_load('collection_nav');
					$navset->options['asNavFor'] = '#flexslider-'. $key;
					flexslider_add('navigation-'. $key, $navset);
					flexslider_add('flexslider-'. $key, $optionset);
				break;
				case 'mediaLink':
					if($i == 0) {
						$out .= '<iframe src="'. $media['content'] .'" width="100%" height="500" frameborder="0" style="border:0" allowfullscreen';
						$out .= isset($asset['title']) ? ' title="'. $media['title'] .'"' : '';
						$out .= '></iframe>';
						$mediaFloat = FALSE;
						dpm($i);
					}
					else {
						$image = '<img src="'. $media['thumbnail'] .'" alt="thumbnail" />';
						$out .= l($image, $media['content'], $media['link']['options']);
						$out .= '<div class="description">'. $media['title'] .'</div>';
					}
				break;
				case 'mediaDownload':
						$image = '<img src="'. $media['thumbnail'] .'" alt="thumbnail" />';
						$out .= l($image, $media['link']['path'], $media['link']['options']);
						// $out .= '<div class="description">'. $media['title'] .'</div>';
				break;
				default:
					$response = isUrlExists($media['content']);
					if ($response['status'] && $type !='slideshowHTML') {
						$out .= '<iframe src="'. $media['content'] .'" width="100%" height="500" frameborder="0" style="border:0"';
						$out .= isset($asset['title']) ? ' title="'. $media['title'] .'"' : '';
						$out .= '></iframe>';
						$mediaFloat = FALSE;
					}
					else {
						$image = isset($media['title']) ? '<img src="'. $media['thumbnail'] .'" alt="'. $media['title'] .'" />' : '<img src="'. $media['thumbnail'] .'" alt="thumbnail" />';
						$out .= l($image, $media['content'], array('attributes' => array('target' => '_blank'), 'html'=> TRUE));
					}
				break;
			}
			$out .= '</div>';
		}

		$i++;
		$out .= '</div>';
 }

	return array(
		'content' => $out,
		'mediaFloat' => $mediaFloat
	);
}


