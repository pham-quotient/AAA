<?php

/**
 * @file
 * Defines a simple 2-column grid layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Fluid Two Column Stacked, Right Aside'),
  'icon' => 'preview.png',
  'category' => t('Omega content layouts'),
  'theme' => 'two_col_right_stacked',
  'css' => '../../../css/layouts/two-col/two-col.layout.css',
  'regions' => array(
    'feature' => t('Feature Content'),
    'main' => t('Main Column'),
    'aside' => t('Right Aside'),
  ),
);

/**
 * Implements hook_preprocess_grid_3().
 */
function template_preprocess_two_col_right_stacked(&$variables) {
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'][] = 'panel-display--two-col-right';

  foreach($variables['content'] as $name => $item) {
    $variables['region_attributes_array'][$name]['class'][] = 'two-col-region';
    $variables['region_attributes_array'][$name]['class'][] = 'two-col-region--' . drupal_clean_css_identifier($name);
  }
}
