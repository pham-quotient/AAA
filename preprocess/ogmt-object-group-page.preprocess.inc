<?php

/**
 * Implements hook_preprocess_page().
 */
function si_aaa_preprocess_ogmt_object_group_page(&$variables) {
	$si_ogmt = variable_get('si_ogmt_view', array());
  $variables['parent_title'] = $variables['node'] ='';

	if (isset($si_ogmt['si_content']) && empty($variables['page'])) {
		list($name, $display) = explode(':', $si_ogmt['si_content']);
		$variables['si_content'] =views_embed_view($name, $display, $variables['objectGroupId']);

	}
	$variables['menu'] = si_ogmt_build_menu($variables['raw_object_group_page']);
  if (!empty( $variables['raw_object_group_page']['page'])) {
    $variables['parent_title'] = $variables['raw_object_group_page']['title'];
  }

  else {
    $query = db_query('SELECT entity_id FROM {field_data_ogmt_objectgroupid} WHERE ogmt_objectgroupid_value = :oid', array('oid' => $variables['objectGroupId']));
    $nid = $query->fetchField();
    if ($nid) {
      $node = node_load($nid);
      $variables['node'] = node_view($node, 'teaser');
    }
  }
}



/**
 * Renders a menu from a menu object
 */
function si_ogmt_build_menu($object_group_page) {
  if (empty($object_group_page['menu'])) {
    return '';
  }

  $bp = _ogmt_variable_get('menu_base_pages');
  $bp .= '/' . $object_group_page['url'];
  $menu = '';
	$menu = '<li>'. l(t('Overview'), $bp) .'</li>';
  foreach($object_group_page['menu'] as $page) {
    $menu .= '<li>' . l($page['title'], $bp . '/' . $page['url']) . '</li>';
  }

  if (!empty($menu)) {
    $menu = '<ul class="menu">' . $menu . '</ul>';
  }

  return $menu;
}