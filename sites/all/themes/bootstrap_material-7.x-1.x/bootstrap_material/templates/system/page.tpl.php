<div class="demo-layout mdl-layout mdl-js-layout mdl-layout--fixed-drawer mdl-layout--fixed-header">
  <div class="demo-layout-transparent mdl-layout mdl-js-layout mdl-js-layout mdl-layout--fixed-header">
    <header class="mdl-layout__header mdl-layout__header--grey">
      <div class="mdl-layout__header-row">
        <!-- Title -->
        <?php if ($logo): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo" style="padding: 0px !important; margin: 0px !important; width: 8%;">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" style="width: 50%; margin: 10px; float: left;"/>
          </a>
        <?php endif; ?>
        <div id="site-name"<?php //if ($hide_site_name) { print ' class="element-invisible"'; } ?>>
          <strong>
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span class="mdl-layout-title"><?php print $site_name; ?></span></a>
          </strong>
        </div>
        <!-- Navigation -->
        
        <!-- Add spacer, to align navigation to the right -->
        <!-- Navigation -->
        <?php print render($page['header']); ?>
      </div>
    </header>
    <div class="demo-drawer mdl-layout__drawer mdl-color--blue-grey-900 mdl-color-text--blue-grey-50">
      <header class="demo-drawer-header">
        <?php print render($page['sidenav_top']); ?>
      </header>
      <?php print render($page['sidenav']); ?>
    </div>
  </div>
  <?php if(!$logged_in):?>
  <a href="https://github.com/google/material-design-lite/blob/mdl-1.x/templates/dashboard/" target="_blank" id="view-source" class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored mdl-color-text--white">View Source</a>
  <div class="site-content">
    <div class="mdl-grid">
      <?php if($is_front):?><div class="mdl-cell mdl-cell--12-col" style="background: WHITE; padding: 20px;"><?php print render($page['banner']); ?></div><?php endif;?>
    </div>
    <?php if ($page['bc_fp_1']): ?>
      <div class="mdl-grid">
        <?php if ($page['bc_fp_1']): ?>
            <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['bc_fp_1']); ?></div><?php endif;?>
        <?php endif; ?>
        <?php if ($page['bc_fp_2']): ?>
          <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['bc_fp_2']); ?></div><?php endif;?>
        <?php endif; ?>
        <?php if ($page['bc_fp_3']): ?>
          <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['bc_fp_3']); ?></div><?php endif;?>
        <?php endif; ?>
      </div>
    <?php endif; ?>
    <div class="mdl-grid">
      <div class="mdl-cell mdl-cell--8-col" style="background: WHITE; padding: 20px;"><?php print render($page['content']); ?></div>
      <div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['sidebar']); ?></div>
    </div>
    <div class="mdl-grid">
      <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['fp_1']); ?></div><?php endif;?>
      <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['fp_2']); ?></div><?php endif;?>
      <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['fp_3']); ?></div><?php endif;?>
    </div>
    <div class="mdl-grid">
      <div class="mdl-cell mdl-cell--12-col" style="background: WHITE; padding: 20px;"><?php print render($page['after_content']); ?></div>
    </div>
    <div class="mdl-grid">
        <div class="mdl-cell mdl-cell--12-col" style="background: #778899; padding: 20px;"><?php print render($page['footer']); ?>
        <div class="mdl-grid">
          <div class="mdl-cell mdl-cell--4-col" style="background: #C0C0C0; padding: 20px;"><?php print render($page['footer_col1']); ?></div>
          <div class="mdl-cell mdl-cell--4-col" style="background: #C0C0C0; padding: 20px;"><?php print render($page['footer_col2']); ?></div>
          <div class="mdl-cell mdl-cell--4-col" style="background: #C0C0C0; padding: 20px;"><?php print render($page['footer_col3']); ?></div>
        </div>
        <div class="mdl-grid">
          <div class="mdl-cell mdl-cell--12-col" style="background: WHITE; padding: 20px;"><?php print render($page['footer_bottom']); ?></div>
        </div>
        </div>
      </div>
    </div>
      <?php endif;?>
      <?php if($logged_in):?>
  <a href="https://github.com/google/material-design-lite/blob/mdl-1.x/templates/dashboard/" target="_blank" id="view-source" class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored mdl-color-text--white">View Source</a>
  <div class="site-content">
    <div class="mdl-grid">
      <?php if($is_front):?><div class="mdl-cell mdl-cell--12-col" style="background: WHITE; padding: 20px;"><?php print render($page['banner']); ?></div><?php endif;?>
    </div>
    <?php if ($page['bc_fp_1']): ?>
      <div class="mdl-grid">
        <?php if ($page['bc_fp_1']): ?>
            <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['bc_fp_1']); ?></div><?php endif;?>
        <?php endif; ?>
        <?php if ($page['bc_fp_2']): ?>
          <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['bc_fp_2']); ?></div><?php endif;?>
        <?php endif; ?>
        <?php if ($page['bc_fp_3']): ?>
          <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['bc_fp_3']); ?></div><?php endif;?>
        <?php endif; ?>
      </div>
    <?php endif; ?>
    <div class="mdl-grid">
      <div class="mdl-cell mdl-cell--8-col" style="background: WHITE; padding: 20px;"><?php print render($page['content']); ?></div>
      <div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['sidebar']); ?></div>
    </div>
    
    <div class="mdl-grid">
      <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['fp_1']); ?></div><?php endif;?>
      <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['fp_2']); ?></div><?php endif;?>
      <?php if($is_front):?><div class="mdl-cell mdl-cell--4-col" style="background: WHITE; padding: 20px;"><?php print render($page['fp_3']); ?></div><?php endif;?>
    </div>
    <div class="mdl-grid">
      <div class="mdl-cell mdl-cell--12-col" style="background: WHITE; padding: 20px;"><?php print render($page['after_content']); ?></div>
    </div>
    <div class="mdl-grid">
        <div class="mdl-cell mdl-cell--12-col" style="background: #778899; padding: 20px;"><?php print render($page['footer']); ?>
        <div class="mdl-grid">
          <div class="mdl-cell mdl-cell--4-col" style="background: #C0C0C0; padding: 20px;"><?php print render($page['footer_col1']); ?></div>
          <div class="mdl-cell mdl-cell--4-col" style="background: #C0C0C0; padding: 20px;"><?php print render($page['footer_col2']); ?></div>
          <div class="mdl-cell mdl-cell--4-col" style="background: #C0C0C0; padding: 20px;"><?php print render($page['footer_col3']); ?></div>
        </div>
        <div class="mdl-grid">
          <div class="mdl-cell mdl-cell--12-col" style="background: WHITE; padding: 20px;"><?php print render($page['footer_bottom']); ?></div>
        </div>
        </div>
      </div>
    </div>
      <?php endif;?>
  </div>
      
</div>