<?php

/**
 * @file
 * Contains the theme function override for 'menu links'.
 */

/**
 * Returns HTML for a menu link.
 *
 * @ingroup themeable
 */
function si_aaa_menu_link($variables) {
  $element = $variables ['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  //$options = empty($element['#localized_options']) ? array() : $element['#localized_options'];
  //$options['html'] = TRUE;
  $element['#localized_options']['html'] = TRUE;
  $title = '<span class="menu-title">'. $element['#title'] .'</span>';
  $output = l($title, $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
