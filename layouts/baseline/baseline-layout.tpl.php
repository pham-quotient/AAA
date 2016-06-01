<div<?php print $attributes; ?>>
  <header class="l-header" role="banner">
    <?php if (!empty($page['header_preface_left']) || !empty($page['header_preface_right'])): ?>
      <div class="l-header-preface-wrapper">
      	<div class="l-outer">
		  		<?php if (!empty($page['header_preface_left'])): ?>
            <?php print render($page['header_preface_left']); ?>
          <?php endif; ?>
          <?php if (!empty($page['header_preface_right'])): ?>
          	<div class="l-region-header-preface-right-wrapper">
	            <?php print render($page['header_preface_right']); ?>
  					</div>
           
          <?php endif; ?>
        </div>
      </div>
    <?php endif; ?>
    <div class="l-container l-header-middle">
      	<div class="l-region l-branding site-branding">
          <?php if ($site_name || $site_slogan): ?>
            <?php if ($site_name): ?>
              <h1 class="site-name">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </h1>
            <?php endif; ?>

            <?php if ($site_slogan): ?>
              <h2 class="site-slogan"><?php print $site_slogan; ?></h2>
            <?php endif; ?>
          <?php endif; ?>
          <?php print render($page['branding']); ?>
      	</div>
        <div class="l-region--header-wrapper">
      	<?php print render($page['header']); ?>
        </div>
   	</div>
		<?php print render($page['navigation']); ?>
  </header>

  <?php if (!empty($page['hero'])): ?>
    <div class="l-hero">
      <div class="l-container">
        <?php print render($page['hero']); ?>
      </div>
    </div>
  <?php endif; ?>
  <?php if (!empty($page['highlighted'])): ?>
    <div class="l-highlighted">
      <?php print render($page['highlighted']); ?>
    </div>
  <?php endif; ?>

  <div class="l-main l-container">
    <a id="main-content"></a>
<?php /*?>    <?php print $breadcrumb; ?>
<?php */?>

    <div class="l-content" role="main">
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php print render($tabs); ?>
      <?php print render($page['help']); ?>      
      
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php print $feed_icons; ?>
    </div>

    <?php print render($page['sidebar_first']); ?>
    <?php print render($page['sidebar_second']); ?>
  </div>

  <div class="l-footer-preface" role="complementary">
    <div class="l-container">
     <?php print render($page['footer_preface']); ?>
    </div>
  </div>

  <footer class="l-footer" role="contentinfo">
    <div class="l-container">
      <?php print render($page['footer']); ?>
    </div>
  </footer>
</div>
