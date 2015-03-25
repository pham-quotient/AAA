<?php

/**
 * @file
 * Defines a simple 2-column grid layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Fluid Two Column Stacked'),
  'icon' => 'preview.png',
  'category' => t('Omega content layouts'),
  'theme' => 'two_col_stacked',
  'css' => '../../../css/layouts/two-col-stacked/two-col-stacked.layout.css',
  'regions' => array(
    'feature' => t('Feature Content')
    'first' => t('First'),
    'second' => t('Second'),
  ),
);

/**
 * Implements hook_preprocess_grid_3().
 */
function template_preprocess_grid_3(&$variables) {
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'][] = 'panel-display--grid-3';

  foreach($variables['content'] as $name => $item) {
    $variables['region_attributes_array'][$name]['class'][] = 'grid-3-region';
    $variables['region_attributes_array'][$name]['class'][] = 'grid-3-region--' . drupal_clean_css_identifier($name);
  }
}
