<div <?php print $attributes;?> class="<?php print $classes;?>">
  <?php if($section == 'frontend') :?>
    <button data-target=".nav-collapse" data-toggle="collapse" class="btn btn-navbar tb-megamenu-button" type="button">
    	<?php if ($icon_class) : ?>
      <span class="menu-icon fa fa-bars"></span>
      <?php endif;?>
      <span class="menu-title"><?php print $menu_title ?></span>
    </button>
    <div class="nav-collapse collapse<?php print $block_config['always-show-submenu'] ? ' always-show' : '';?>">
  <?php endif;?>
  <?php print $content;?>
  <?php if($section == 'frontend') :?>
    </div>
  <?php endif;?>
</div>
