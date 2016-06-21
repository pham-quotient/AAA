<?php 
  dpm($variables);
?>
<!-- Remove Facets Links -->
<?php if($active_facets): ?>
  <div id="remove_facets_links">
    <?php print $active_facets; ?>
  </div>
<?php endif; ?>

<!-- Render the Filter Tab Menus -->
<?php if($filter_menus['tabs']): ?>
  <?php print drupal_render($filter_menus['tabs']); ?>
<?php endif; ?>

<div class="edan-search clearfix <?php print variable_get('si_edan_default', 'list-view'); ?>">

  <?php print $pager; ?>

  <div class="edan-results-summary"><?php print($results_summary); ?></div>
  <div class="<?php print $container_class; ?>">
    <ul class="search-results<?php print $results_class; ?>">


    </ul>
  </div>


  <?php print $pager; ?>
</div>