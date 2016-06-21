<?php

/**
 * Implements hook_preprocess_page().
 */
function si_aaa_preprocess_node(&$variables) {
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
	$node = $variables ['node'];
	$lang = $variables['language'];

	if ($node->type == 'promo') {
		$variables['link_url'] = $variables['link_attributes'] = '';
		if (!empty($variables['field_link_single'])) {
			$item = $variables['field_link_single'][$lang][0];
			$variables['link_url'] = url($item['url']);
			$variables['link_attributes'] = empty($item['attributes']) ? '' : drupal_attributes($item['attributes']);
		}
	}
//	dpm($variables);
	if (isset($variables['content']['links']['node']['#links']['node-readmore'])) {
		$variables['content']['links']['node']['#links']['node-readmore']['title'] =t('Learn more <span class="sr-only">about @title</span>', array('@title' => $node->title));
	}
}
