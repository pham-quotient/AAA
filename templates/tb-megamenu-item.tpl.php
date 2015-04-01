<li <?php print $attributes;?> class="<?php print $classes;?>">
  <a href="<?php print in_array($item['link']['href'], array('<nolink>')) ? "#" : url($item['link']['href']);?>" class="<?php print implode(" ", $a_classes);?>">
    <?php if(!empty($item_config['xicon'])) : ?>
      <span class="<?php print $item_config['xicon'];?>"></span>
    <?php endif;?>
    <?php if($attributes_array['data-level'] == 1): ?>
      <span class="menu-title">
      <?php print t($item['link']['link_title']);?>
      </span>
    <?php else: ?>
      <?php print t($item['link']['link_title']);?>
    <?php endif;?>
    <?php if($submenu && $block_config['auto-arrow']) :?>
      <span class="caret"></span>
    <?php endif;?>
    <?php if(!empty($item_config['caption'])) : ?>
      <span class="mega-caption"><?php print t($item_config['caption']);?></span>
    <?php endif;?>
  </a>
  <?php print $submenu ? $submenu : "";?>
</li>
