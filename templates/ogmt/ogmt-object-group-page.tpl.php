<?php 
/**
 * Theme Object Group Page
 */ 
//dpm($variables['object_group_page_object']);  
dpm($variables);
?>


<div class="ogmt-group-wrapper two-col-left panel-display panel-display--two-col">
  <div class="l-region--main<?php print $menu ? ' has-sidebar-first' : '' ?>">


    <div class="ogmt-og-content-wrapper">
      <h1 class="object-title">
        <?php if ($parent_title): ?>
          <span>
            <?php print $parent_title; ?>
         </span>
        <?php endif; ?>
        <?php print $title; ?>
      </h1>
      <div class="ogmt-og-content">
      <?php if ($si_content): ?>
        <?php print $si_content; ?> 
        <?php else: ?>
          <?php if (isset($feature_image_url)): ?>
          <div class="object-thumbnail">
            <img src="<?php print $feature_image_url; ?>" />
          </div>
        <?php endif; ?>
      <?php print $content; // RB moved 20160112 - was just above the closing endif, previous line ?>

      <?php endif; ?>



    </div>
  	</div>
    <?php if ($search_results): ?>
      <?php print $search_results; ?>
    <?php endif; ?>
  </div>

  <?php if ($menu): ?>
    <aside class="l-region--left"><?php print $menu; ?></aside>
  <?php endif; ?>

</div>