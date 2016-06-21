<?php

/**
 * Implements hook_preprocess_page().
 */
function si_aaa_preprocess_edan_search_results(&$vars) {
//	$docs = $variables['docs'];
//	$query = drupal_get_destination();
////	dpm($query);
//	foreach ($docs as $key => $doc) {
//		$attributes = array();
//		$attributes['class'][] = 'edan-search-result';
//		$attributes['class'][] = isset($doc['flags']['in_list']) && $doc['flags']['in_list'] === TRUE ? ' in-list' : '';
//    $attributes['class'][] = isset($doc['flags']['in_unit']) && $doc['flags']['in_unit'] === TRUE ?' in-unit' : '';
//		$attributes['class'] = array_filter($attributes['class']);
//		$attributes['id'] = $doc['content']['descriptiveNonRepeating']['record_ID'];;
//		$docs[$key]['row_attributes'] = $attributes;
//		// Validate thumbnail url
//		if (isset($doc['content']['descriptiveNonRepeating']['online_media']['media'])) {
//			$media = $doc['content']['descriptiveNonRepeating']['online_media']['media'][0];
//			$response = isUrlExists($media['thumbnail']);
//		//	dpm($response);
//			if (!$response['status']) {
//				unset($docs[$key]['content']['descriptiveNonRepeating']['online_media']['media']);
//			}
//		}
//		if (isset($doc['#title_link']) && !empty($doc['#title_link'])) {
//			// Validate object link
////			$url = url($doc['#title_link']['path'], array('query' => $doc['#title_link']['query'], 'fragment' => $doc['#title_link']['fragment']));
////			$response = isUrlExists($url);
////			dpm($response);
////			if ($response['status']) {
//				$query = array_merge($doc['#title_link']['query'], $query);
//				$docs[$key]['#title'] = l($doc['#title_plain'], $doc['#title_link']['path'], array('query' => $query, 'fragment' => $doc['#title_link']['fragment'], 'html'=> TRUE));
//				$docs[$key]['#title_link']['query'] = $query;
//			//}
////			else {
////				$docs[$key]['#title'] = $doc['#title_plain'];
////			}
//		}
//
//		if(array_key_exists('indexedStructured', $doc['content'])) {
//			// create a template for the array we're expecting:
//			$structuredIndexTemplate = array(
//				'geoLocation' => array(
//					0 => array(
//						'points' => array(
//							'point' => array (
//								'latitude' => array(
//									'content'
//								),
//								'longitude' => array(
//									'content'
//								)
//							)
//						)
//					)
//				)
//			);
//			$structuredIndex = array_merge($structuredIndexTemplate, $doc['content']['indexedStructured']);
//			$latitude = isset($structuredIndex['geoLocation'][0]['points']['point']['latitude']['content'])
//				? $structuredIndex['geoLocation'][0]['points']['point']['latitude']['content']
//				: '';
//			$longitude = isset($structuredIndex['geoLocation'][0]['points']['point']['longitude']['content'])
//				? $structuredIndex['geoLocation'][0]['points']['point']['longitude']['content']
//				: '';
//			if(strlen($latitude) > 0 || strlen($longitude) > 0) {
//				$docs[$key]['content']['freetext']['geoLocation_0'] = array(
//					array(
//						'label' => t('Geographic Location'),
//						'content' => $latitude . ', ' . $longitude
//					)
//				);
//			}
//		}
//	}
//	$variables['docs'] = $docs;
	// dumper($vars['docs']);

	$query_params = drupal_get_query_parameters();

	// Expand upon the results_summary variable coming from the EDAN Search module.
	$page = isset($query_params['page']) ? ((int)$query_params['page'] + 1) : 1;
	$total_results = $vars['results_summary'];
	$num_found = $vars['numFound'];
	$end = $page*$num_found;
	$start = $end-($num_found-1);
	$vars['results_summary'] = 'Showing ' . $start . ' - ' . $end . ' of ' . $total_results . ' result(s).';

	// Facet Filter Menus
	// Process URL
	$url = '?' . drupal_http_build_query($query_params);
	// Process Facet Filters
	$filters = _edan_extended_process_facet_filters( $vars['facets_raw'], $url );
	// Render Filter Menus
	$vars['filter_list'] = $filters;
	$vars['filter_menus'] = _edan_extended_render_filter_menus( $filters );

	// Set up the background_style and grid_3_region_class variables for the template.
	foreach ($vars['docs'] as $doc_key => $doc_value) {

		// Set the image background, if there's an acceptable one to display.
		$background_style = '';
		$ids_url = 'https://ids.si.edu/ids/deliveryService/?id=';
		$image_blacklist = array(
			'http://sirismm.si.edu/siris/FullyDigitized.gif',
			'http://sirismm.si.edu/siris/thbtrans.gif',
			'http://sirismm.si.edu/siris/sound.gif',
		);

		if(!empty($doc_value['content']['descriptiveNonRepeating'])
			&& !empty($doc_value['content']['descriptiveNonRepeating']['online_media'])
			&& (int)$doc_value['content']['descriptiveNonRepeating']['online_media']['mediaCount']) {
			$thumbnail_image = $doc_value['content']['descriptiveNonRepeating']['online_media']['media'][0]['thumbnail'];
			$full_image = str_replace('/thumbnail/', '/reference/', $thumbnail_image);
			// Set the style attribute value.
			$background_style = !in_array($full_image, $image_blacklist)
				? 'background: #000 url(' . $ids_url . $full_image . '?max_w=500) no-repeat center center;' : '';
		}

		// Establish the CSS class for the grid item.
		switch($doc_key) {
			case 0:
			case 3:
			case 6:
				$grid_3_region_class = 'first clearfix';
				break;
			case 1:
			case 4:
			case 7:
				$grid_3_region_class = 'second';
				break;
			case 2:
			case 5:
			case 8:
				$grid_3_region_class = 'third';
				break;
		}

		// TODO: The setting of the local_record_link is temporary.
		// AAA would like all of their URLs to match their current website.
		// Examples:
		// /collections/betty-parsons-gallery-records-and-personal-papers-7211
		// /collections/interviews/oral-history-interview-mark-adams-and-beth-van-hoesen-12674
		// /collections/items/detail/l-brent-kington-his-workshop-1134
		$base_record_url = url(_edan_record_variable_get('menu_record_page'), array('absolute' => true, 'alias' => false ));
		$vars['docs'][$doc_key]['local_record_link'] = $base_record_url . '/' . $doc_value['type'] . '/'. str_replace($doc_value['type'] . '-', '', $doc_value['id']) . '/';

		// Get the record title.
		$vars['docs'][$doc_key]['record_title'] = app_util_get_title( $vars['docs'][$doc_key] );

		$vars['docs'][$doc_key]['background_style'] = $background_style;
		$vars['docs'][$doc_key]['grid_3_region_class'] = $grid_3_region_class;
	}

//	return theme('edan_search_results', $vars);
}