<?php

function si_aaa_book_navigation($node) {
  $output = '';
  $links = '';

  if ($node->nid) {
    $tree = book_tree($node->nid);

    if ($prev = book_prev($node)) {
      drupal_add_link(array('rel' => 'prev', 'href' => url('node/' . $prev->nid)));
      $links .= l(t('‹ ') . $prev->title, 'node/' . $prev->nid, array('class' => 'page-previous', 'title' => t('Go to previous page')));
    }
    if ($node->parent) {
      drupal_add_link(array('rel' => 'up', 'href' => url('node/' . $node->parent)));
      $links .= l(t('Back to Index Page'), 'node/' . $node->parent, array('class' => 'page-up', 'title' => t('Go to parent page')));
    }
    if ($next = book_next($node)) {
      drupal_add_link(array('rel' => 'next', 'href' => url('node/' . $next->nid)));
      $links .= l($next->title . t(' ›'), 'node/' . $next->nid, array('class' => 'page-next', 'title' => t('Go to next page')));
    }

    if (isset($tree) || isset($links)) {
      $output = '<div class="book-navigation">';
      if (isset($tree)) {
        $output .= $tree;
      }
      if (isset($links)) {
        $output .= '<div class="page-links clear-block">' . $links . '</div>';
      }
      $output .= '</div>';
    }
  }

  return $output;
}