<pre>;
<?php print_r($variables) ;?>
</pre>

<div class="ogmt-og-content-test"><?php echo $content; ?></div>

<?php if ($menu): ?>
  <div class="ogmt-og-menu"><?php echo $menu; ?></div>
<?php endif; ?>

<?php /*render($node->field_mycustomfield);*/ ?>

<?php if ($search_results): ?>
  <div>
  <?php echo $search_results; ?>
  </div>
<?php endif; ?>

