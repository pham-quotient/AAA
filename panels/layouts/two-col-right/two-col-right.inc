<?php

/**
 * @file
 * Defines a simple 2-column grid layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Two column right aside'),
  'icon' => 'preview.png',
  'category' => t('Columns: 2'),
  'theme' => 'two_col_right',
  'css' => '../../../css/layouts/panels/panels.layout.css',
  'regions' => array(
    'hero' => t('Hero'),
    'main' => t('Main Content'),
    'right' => t('Right Aside'),
  ),
);

/**
 * Implements hook_preprocess_grid_3().
 */
function template_preprocess_two_col_right(&$variables) {
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'][] = 'panel-display--two-col';

  foreach($variables['content'] as $name => $item) {
    $variables['region_attributes_array'][$name]['class'][] = 'l-region--' . drupal_clean_css_identifier($name);
		if ($name == 'main' && !empty($variables['content']['right'])) {
			 $variables['region_attributes_array'][$name]['class'][] = 'has-sidebar-second';
		}
  }

}
