<?php

/**
 * Implements hook_preprocess_tb_megamenu_nav().
 */
function si_aaa_preprocess_tb_megamenu_nav(&$vars) {
  $items = $vars['items'];
  $level = $vars['level'];
  $names = menu_get_menus();
  $lis = array();
  foreach ($items as $item) {
    if(!$item['link']['hidden']) {
      $lis[] = theme('tb_megamenu_item', array(
        'menu_name' => $vars['menu_name'],
        'level' => $level + 1,
        'item' => $item,
        'menu_config' => $vars['menu_config'],
        'block_config' => $vars['block_config'],
        'trail' => $vars['trail'],
        'section' => $vars['section'],
      ));
    }
  }
  $vars['lis'] = implode("\n", $lis);
  $vars['classes_array'][] = "nav";
  $vars['classes_array'][] = "level-" . $level;
  $vars['classes_array'][] = "items-" . count($items);
  $vars['menu_title'] = current($names);
}
