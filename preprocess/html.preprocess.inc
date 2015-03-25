<?php

/**
 * Implements hook_preprocess_page().
 */
function si_aaa_preprocess_html(&$variables) {
  drupal_add_css(path_to_theme() . '/css/font-awesome/font-awesome-ie7.css',
    array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
}
