<?php

/**
 * @file
 * Defines a simple 2-column grid layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Two column left aside'),
  'icon' => 'preview.png',
  'category' => t('Columns: 2'),
  'theme' => 'two_col_left',
  'css' => '../../../css/layouts/panels/panels.layout.css',
  'regions' => array(
    'hero' => t('Hero'),
    'main' => t('Main Content'),
    'tab' => t('Tab Content'),
    'left' => t('Left Aside'),
  ),
);

/**
 * Implements hook_preprocess_grid_3().
 */
function template_preprocess_two_col_left(&$variables) {
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'][] = 'panel-display--two-col';

  foreach($variables['content'] as $name => $item) {

		if ($name == 'main') {
			// $variables['region_attributes_array'][$name]['class'][] = 'has-sidebar-first';
      $variables['region_attributes_array'][$name]['class'][] = 'main-content';
    }
    else {
      $variables['region_attributes_array'][$name]['class'][] = 'l-region--' . drupal_clean_css_identifier($name);
    }
  }

}
