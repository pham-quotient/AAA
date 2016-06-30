<?php 
/**
 * Theme Object Group Page
 */ 
//dpm($variables['object_group_page_object']);  
dpm($variables);
?>


<div class="ogmt-group-wrapper two-col-left panel-display panel-display--two-col">
  <div class="l-region--main<?php print $menu ? ' has-sidebar-first' : '' ?>">

      <div class="ogmt-og-content">
        <?php if ($parent_title): ?>
          <div class="parent-title">
              <?php print $parent_title; ?>
           </div>
        <?php endif; ?>

        <?php if ($node): ?>
        <?php print render($node); ?>
        <?php else: ?>
          <h1 class="page-title">
            <?php print $title; ?>
          </h1>
      <?php print $content; // RB moved 20160112 - was just above the closing endif, previous line ?>

      <?php endif; ?>



    </div>
    <?php if ($search_results): ?>
      <?php print $search_results; ?>
    <?php endif; ?>
  </div>

  <?php if ($menu): ?>
    <aside class="l-region--left"><?php print $menu; ?></aside>
  <?php endif; ?>

</div>