<?php

/**
 * Implements hook_preprocess_tb_memgamenu().
 */
function si_aaa_preprocess_tb_megamenu(&$vars) {
  $menu_name = $vars['menu_name'];
  $menu_names = menu_get_menus();

  if($vars['section'] == 'backend') {
    $items = tb_megamenu_get_tree($menu_name);
  }
  else {
    $items = menu_tree_all_data($menu_name);
  }
  if (function_exists('i18n_menu_localize_tree')) {
    $items = i18n_menu_localize_tree($items);
  }
  $items_page = menu_tree_page_data($menu_name);
  $trail = tb_megamenu_build_page_trail($items_page);
  $menu_config = tb_megamenu_get_menu_config($menu_name);
  $block_config = tb_megamenu_get_block_config($menu_name);
  tb_megamenu_sync_config_all($items, $menu_config, $vars['section']);
  tb_megamenu_edit_block_config($block_config);
  $vars['classes_array'][] = "tb-megamenu-" . str_replace('_', '-', $menu_name);
  if($vars['section'] == 'frontend' && $block_config['style'] != '') {
    drupal_add_css(drupal_get_path("module", "tb_megamenu") . "/css/styles/" . $block_config['style'] . ".css", array(
        'basename' => "tb-megamenu-style-" . $block_config['style'] . ".css",
      ));
    $vars['classes_array'][] = "style-" . $block_config['style'];
  }
  if($block_config['animation'] != 'none') {
    $vars['classes_array'][] = "animate";
    $vars['classes_array'][] = $block_config['animation'];
    $vars['attributes_array']['data-duration'] = $block_config['duration'];
    $vars['attributes_array']['data-delay'] = $block_config['delay'];
    $vars['attributes_array']['id'] = "tb-megamenu-" . str_replace('_', '-', $menu_name);
  }
  $vars['content'] = theme('tb_megamenu_nav', array(
    'menu_name' => $vars['menu_name'],
    'level' => 0,
    'menu_config' => $menu_config,
    'block_config' => $block_config,
    'items' => $items,
    'trail' => $trail,
    'section' => $vars['section'],
  ));
  $vars['block_config'] = $block_config;
  if($vars['section'] == 'frontend' && $block_config['animation'] != 'none') {
    $css = array();
    $css[] = '.tb-megamenu.animate .mega > .mega-dropdown-menu, .tb-megamenu.animate.slide .mega > .mega-dropdown-menu > div {';
    $css[] = '  transition-delay: ' . $block_config['delay'] . 'ms;';
    $css[] = '  -webkit-transition-delay: ' . $block_config['delay'] . 'ms;';
    $css[] = '  -ms-transition-delay: ' . $block_config['delay'] . 'ms;';
    $css[] = '  -o-transition-delay: ' . $block_config['delay'] . 'ms;';
    $css[] = '  transition-duration: ' . $block_config['duration'] . 'ms;';
    $css[] = '  -webkit-transition-duration: ' . $block_config['duration'] . 'ms;';
    $css[] = '  -ms-transition-duration: ' . $block_config['duration'] . 'ms;';
    $css[] = '  -o-transition-duration: ' . $block_config['duration'] . 'ms;';
    $css[] = '}';
    drupal_add_css(implode("\n", $css), array('type' => 'inline'));
  }
  $vars['menu_title'] = $menu_name == 'main-menu' ? t('Menu') : $menu_names[$menu_name];
	$vars['icon_class'] = $menu_name == 'main-menu' ? 'fa fa-bars' : '';
}
