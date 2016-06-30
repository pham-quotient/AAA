<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * {{ THEME NAME }} theme.
 */

  /**
   * Remove the unneeded favicon from the head section.
   */
  function si_aaa_html_head_alter(&$head_elements) {
    
    foreach ($head_elements as $key => $element) {
      if (!empty($element['#attributes'])) {
        if (array_key_exists('href', $element['#attributes'])) {
          if (strpos($element['#attributes']['href'], 'misc/favicon.ico') > 0) {
            unset($head_elements[$key]);
          }
        }
      }
    }
  }

/**
* Send an HTTP request to a the $url and check the header posted back.
*
* @param $url String url to which we must send the request.
* @param $failCodeList Int array list of code for which the page is considered invalid.
*
* @return status and header info
*/
function isUrlExists($url, array $failCodeList = array(404)){

  $exists = false;
//		$proto = '((https?|ftp)\:\/\/)?';
//			preg_match("/^$proto/", $url, $matches);
  //	if (pre_match('

  $regex = "((https?|ftp)\:\/\/)?"; // Scheme
  $regex .= "([a-z0-9+!*(),;?&=\$_.-]+(\:[a-z0-9+!*(),;?&=\$_.-]+)?@)?"; // User and Pass
  $regex .= "([a-z0-9-.]*)\.([a-z]{2,3})"; // Host or IP
  $regex .= "(\:[0-9]{2,5})?"; // Port
  $regex .= "(\/([a-z0-9+\$_-]\.?)+)*\/?"; // Path
  $regex .= "(\?[a-z+&\$_.-][a-z0-9;:@&%=+\/\$_.-]*)?"; // GET Query
  $regex .= "(#[a-z_.-][a-z0-9+\$_.-]*)?"; // Anchor
  $headers = FALSE;
  if (preg_match("/^$regex/", $url)) {
    $handle = curl_init($url);


    curl_setopt($handle, CURLOPT_RETURNTRANSFER, true);

    curl_setopt($handle, CURLOPT_SSL_VERIFYPEER, false);

    curl_setopt($handle, CURLOPT_HEADER, true);

    curl_setopt($handle, CURLOPT_NOBODY, true);

    curl_setopt($handle, CURLOPT_USERAGENT, true);


    $headers = curl_exec($handle);

    curl_close($handle);


    if (empty($failCodeList) or !is_array($failCodeList)){

      $failCodeList = array(404);
    }

    if (!empty($headers)){

      $exists = true;

      $headers = explode(PHP_EOL, $headers);
      foreach($failCodeList as $code){

        if (is_numeric($code) and strpos($headers[0], strval($code)) !== false){

          $exists = false;

          break;
        }
      }
    }
  }

  return array(
    'status' => $exists,
    'header' => $headers
  );
}


/**
 * Creates the necessary data structure for edan search results
 */
function _render_edan_search_results(&$vars) {
  //$query = drupal_get_destination();
  $query_params = drupal_get_query_parameters();

  // Expand upon the results_summary variable coming from the EDAN Search module.
  $page = isset($query_params['page']) ? ((int)$query_params['page'] + 1) : 1;
  $total_results = $vars['results_summary'];
  $num_found = $vars['numFound'];
  $end = $page*$num_found;
  $start = $end-($num_found-1);
  $vars['results_summary'] = 'Showing ' . $start . ' - ' . $end . ' of ' . $total_results;

  // Facet Filter Menus
  // Process URL
  $url = '?' . drupal_http_build_query($query_params);
  if(module_exists('edan_extended')) {
    $filters = _edan_extended_process_facet_filters( $vars['facets_raw'], $url );
    // Render Filter Menus
    $vars['filter_menus'] = _si_render_filter_menus( $filters );
  }

  // Process Facet Filters
  $docs = array();
  // Set up the background_style and grid_3_region_class variables for the template.
  foreach ($vars['docs'] as $doc_key => $doc_value) {
    $doc = $doc_value;
    $doc['newMedia'] = '';
    $attributes = array();
    $attributes['class'][] = 'edan-search-result';
    $attributes['class'][] = isset($doc['flags']['in_list']) && $doc['flags']['in_list'] === TRUE ? ' in-list' : '';
    $attributes['class'][] = isset($doc['flags']['in_unit']) && $doc['flags']['in_unit'] === TRUE ? ' in-unit' : '';
    $attributes['class'] = array_filter($attributes['class']);

    $attributes['id'] = isset($doc['content']['descriptiveNonRepeating']['record_ID']) ? $doc['content']['descriptiveNonRepeating']['record_ID'] : rand();

    $doc['record_title'] = app_util_get_title( $vars['docs'][$doc_key] );
    if (!empty($doc_value['content']['descriptiveNonRepeating'])
      && !empty($doc_value['content']['descriptiveNonRepeating']['online_media'])
      && (int)$doc_value['content']['descriptiveNonRepeating']['online_media']['mediaCount']
    ) {
      $media = $doc_value['content']['descriptiveNonRepeating']['online_media']['media'][0];
      $colorbox = module_exists('colorbox');
      $doc['newMedia'] =  $media['type'] == 'Images' ?_process_image($media, $colorbox) : $media;
    }

    $attributes['class'][] = empty($doc['newMedia']) ? 'no-media' : 'has-media';

    $doc['row_attributes'] = $attributes;

    // TODO: The setting of the local_record_link is temporary.
    // AAA would like all of their URLs to match their current website.
    // Examples:
    // /collections/betty-parsons-gallery-records-and-personal-papers-7211
    // /collections/interviews/oral-history-interview-mark-adams-and-beth-van-hoesen-12674
    // /collections/items/detail/l-brent-kington-his-workshop-1134
    $base_record_url = url(_edan_record_variable_get('menu_record_page'), array('absolute' => true, 'alias' => false));
    $doc['local_record_link'] = $base_record_url . '/' . $doc_value['type'] . '/' . str_replace($doc_value['type'] . '-', '', $doc_value['url']) . '/';

    // Get the record title.

    if (isset($doc['#title_link']) && !empty($doc['#title_link'])) {
      $query = array_merge($doc['#title_link']['query'], $query);
      $doc['#title'] = l($doc['#title_plain'], $doc['#title_link']['path'], array('query' => $query, 'fragment' => $doc['#title_link']['fragment'], 'html' => TRUE));
      $doc['#title_link']['query'] = $query;
    }
    // Set up the record type and date.
    $record_type = $date = '';
    if (!empty($doc_value['content']['freetext'])) {
      $doc['record_type'] = !empty($doc_value['content']['freetext']['objectType'][1]['content']) ? $doc_value['content']['freetext']['objectType'][1]['content'] : $doc_value['content']['freetext']['objectType'][0]['content'];
      $doc['record_type'] = str_replace('/', ' / ', $doc['record_type']);

      if (!empty($doc_value['content']['freetext']['date'][1]['content'])) {
        $date = $doc_value['content']['freetext']['date'][1]['content'];
      }
      if (!empty($doc_value['content']['freetext']['date'][0]['content'])) {
        $date = $doc_value['content']['freetext']['date'][0]['content'];
      }
      $doc['date'] = $date;
    }
    // Set up the single search result grid item.
    if (array_key_exists('indexedStructured', $doc['content'])) {
      // create a template for the array we're expecting:
      $structuredIndexTemplate = array(
        'geoLocation' => array(
          0 => array(
            'points' => array(
              'point' => array(
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
      if (strlen($latitude) > 0 || strlen($longitude) > 0) {
        $doc['content']['freetext']['geoLocation_0'] = array(
          array(
            'label' => t('Geographic Location'),
            'content' => $latitude . ', ' . $longitude
          )
        );
      }
    }
    $docs[$doc_key] = $doc;
  }
  $vars['docs'] = $docs;
}

/**
 * Render Filter Menus
 */
function _si_render_filter_menus( $filters ) {
  $filter_menus = $element = $titles = $tabs = array();
  $tabID = drupal_clean_css_identifier('si-tabs-'. REQUEST_TIME . rand());
  // Create the links to remove facets.
  $link = $fq_url_params = '';
  $base_params = $fq_params = array();
  $params = drupal_get_query_parameters();
  $original_params = isset($params['edan_fq']) ? $params['edan_fq'] : '';

  if(isset($params['edan_q']) && isset($params['edan_local'])) {
    $base_params = array(
      'edan_q' => $params['edan_q'],
      'edan_local' => $params['edan_local'],
    );
  }

  $fq_params['edan_fq'] = isset($params['edan_fq']) ? $params['edan_fq'] : '';

  $filter_menus['remove_facets_links'] = '';

  if(!empty($fq_params['edan_fq'])) {
    $filter_menus['remove_facets_links'] .= '<h5>Remove Faceted Filters</h5>' . "\n";
    $filter_menus['remove_facets_links'] .= '<ul>' . "\n";
    foreach($fq_params['edan_fq'] as $fq_key => $fq_value) {
      // Build-out the fq[] url parameters.
      if(!empty($fq_params['edan_fq'])) {
        // Temporarily unset the fq[].
        unset($fq_params['edan_fq'][$fq_key]);
        if(!empty($fq_params['edan_fq'])) {
          // Re-index the edan_fq array.
          $fq_params['edan_fq'] = array_values($fq_params['edan_fq']);
          $fq_url_params = '&' . drupal_http_build_query($fq_params);
        }
      }
      // Set the link.
      $link = '/' . current_path() . '?' . drupal_http_build_query($base_params) . $fq_url_params;
      // Reset the fq[].
      $fq_params['edan_fq'] = $original_params;
      // Format the link text.
      $facet_string = str_replace(':"', ': ', ucwords($fq_value));
      $facet_string = str_replace('"', '', $facet_string);
      $facet_string = str_replace('_', ' ', $facet_string);
      $filter_menus['remove_facets_links'] .= '<li><a href="' . $link . '" title="Click to remove facet">' . t($facet_string . '&nbsp;&nbsp; x') . '</a></li>' . "\n";
    }
    $filter_menus['remove_facets_links'] .= '</ul>' . "\n";
  }

  // Build the list items and div containers with menus in each.

  foreach($filters as $fl_key => $fl_value) {
    if (!empty($fl_value)) {
      asort($fl_value);
      $titles[] = ucwords($fl_key);
      $div = count($fl_value) > 5 ? '<div class="facet-values split-list">' : '<div class="facet-values">';
      $div .= "\n" .'<ul>' . "\n";

      foreach ($fl_value as $filter_key => $filter_value) {
        $div .= '<li class="search-menu-item clearfix"><a href="' . $filter_value . '">' . $filter_key . '</a></li>' ."\n";
      }
      $div .='</ul>' ."\n". '</div>';
      $tabs[] = $div;
    }
  }
  $element = array(
    '#theme' => 'si_field_collection_tabs',
    '#titles' => $titles,
    '#tabs' => $tabs,
    '#tabID' => $tabID,
    '#tabMode' => 'responsive_tab',
    '#prefix' => '<div class="si-tabs responsive-tab" id="'.$tabID .'">',
    '#suffix' => '</div>',
    //'#attached' => $attached,
  );


  $js_settings = array();
  $js_settings['siResponsiveTabs']['tabIDs'][$tabID] =  array(
    'mode' => 'responsive_tab',
    'open' => 0,
  );

  $element['#attached']['js'][] = array(
    'type' => 'setting',
    'data' => $js_settings,
  );
  $filter_menus['tabs'] = $element;
  return $filter_menus;

}

/**
 * add IDS links to images
 * @param $asset
 * @param $colorbox
 * @return array
 */
function _process_image($asset, $colorbox) {
  $item = $asset;
  $options = array();
  $edan_image = variable_get('si_edan_image', array());
  $item['content'] = $asset['content'];
  $item['thumbnail'] = isset($asset['thumbnail']) ? $asset['thumbnail'] : '';
  $link = drupal_parse_url($asset['content']);
  $parsed = parse_url($link['path']);

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

  if ($colorbox) {
    $options['attributes']['class'][] = 'colorbox-load';
    $options['query']['iframe'] = 'true';
    $options['query']['width'] = '85%';
    $options['query']['height'] = '85%';

  }

  $idsID = isset($asset['idsId']) ? $asset['idsId'] : $asset['content'];
  $ids_link = 'http://ids.si.edu/ids/deliveryService';
  $ids_dynamic = 'http://ids.si.edu/ids/dynamic';
  $query = $link['query'];
  $query['max_h'] = isset($edan_image['medium']) ? $edan_image['medium'] : 600;
  $item['content'] = url($ids_link, array('query' => $query)) . '&id=' . $idsID;
  $query['max_h'] = isset($edan_image['thumb']) ? $edan_image['thumb'] : 200;
  $item['thumbnail'] = url($ids_link, array('query' => $query)) . '&id=' . $idsID;
  $link['query']['max_w'] = isset($edan_image['max_width']) ? $edan_image['max_width'] : 980;
  $options['absolute'] = TRUE;
  $options['html'] = TRUE;
  $item['link'] = url($ids_dynamic, $options) . '&id=' . $idsID . '&container.fullpage';

  return $item;
}