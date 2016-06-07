<?php

/**
 * Implements hook_preprocess_comment().
 */
function si_aaa_preprocess_comment(&$variables) {
//	dpm($variables);
	$created = format_date($variables['comment']->created, 'long');
  $variables['submitted'] = t('Posted by @username on !datetime', array('@username' => $variables['comment']->name, '!datetime' => $created));
}