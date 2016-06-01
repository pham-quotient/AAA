<?php

/**
 * Implements hook_preprocess_page().
 */
function si_aaa_preprocess_html(&$variables) {
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
	drupal_add_css(path_to_theme() . '/css/si_aaa.ie-lte-8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 8', '!IE' => FALSE), 'preprocess' => FALSE)); 
	libraries_load('breakpoints');
}
