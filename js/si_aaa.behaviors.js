
(function ($) {
	
  if (!Drupal.si_aaa) {
    Drupal.si_aaa = {};
  }
  var win = $(window);
  /**
   * The recommended way for producing HTML markup through JavaScript is to write
   * theming functions. These are similiar to the theming functions that you might
   * know from 'phptemplate' (the default PHP templating engine used by most
   * Drupal themes including Omega). JavaScript theme functions accept arguments
   * and can be overriden by sub-themes.
   *
   * In most cases, there is no good reason to NOT wrap your markup producing
   * JavaScript in a theme function.
   */


  /**
   * Behaviors are Drupal's way of applying JavaScript to a page. In short, the
   * advantage of Behaviors over a simple 'document.ready()' lies in how it
   * interacts with content loaded through Ajax. Opposed to the
   * 'document.ready()' event which is only fired once when the page is
   * initially loaded, behaviors get re-executed whenever something is added to
   * the page through Ajax.
   *
   * You can attach as many behaviors as you wish. In fact, instead of overloading
   * a single behavior with multiple, completely unrelated tasks you should create
   * a separate behavior for every separate task.
   *
   * In most cases, there is no good reason to NOT wrap your JavaScript code in a
   * behavior.
   *
   * @param context
   *   The context for which the behavior is being executed. This is either the
   *   full page or a piece of HTML that was just added through Ajax.
   * @param settings
   *   An array of settings (added through drupal_add_js()). Instead of accessing
   *   Drupal.settings directly you should use this because of potential
   *   modifications made by the Ajax callback that also produced 'context'.
   */
  Drupal.si_aaa.splitList = function(list, num_cols, listItem) {
    //listItem = 'li',
    listClass = 'sub-list';
    list.each(function() {
      var items_per_col = new Array(),
					newList = 
      items = $(this).find(listItem),
      min_items_per_col = Math.floor(items.length / num_cols),
      difference = items.length - (min_items_per_col * num_cols);
      for (var i = 0; i < num_cols; i++) {
        items_per_col[i] = i < difference ?  min_items_per_col + 1 : min_items_per_col;
      }
      for (var i = 0; i < num_cols; i++) {
        var subClass = 'list-' + i;
        $(this).append($('<ul ></ul>').addClass(listClass +' ' + subClass));
        for (var j = 0; j < items_per_col[i]; j++) {
          var pointer = 0;
          for (var k = 0; k < i; k++) {
            pointer += items_per_col[k];
          }
          $(this).find('.' + subClass).last().append(items[j + pointer]);
        }
      }
    });
  };

  Drupal.si_aaa.resizeImage = function(context) {
    if ($(window).width() > 500) {
      $('.l-content').find('img').each(function () {
        var img = $(this);
        var imgSrc = img.attr('src');
        if (imgSrc.indexOf('http://ids.si.edu/ids/deliveryService') > -1 ) {
       var imgParams = imgSrc.substr(imgSrc.indexOf('?')+1);
          var parentWidth = $(this).parents('.l-content').width();
          var params = imgParams.split('&');
          var newSrc = 'http://ids.si.edu/ids/deliveryService?' + 'max=' + parentWidth + '&' + params[1];
//            console.log(newSrc);
          $(this).attr('src', newSrc);
        }
      });
    }

  };
	
	  Drupal.si_aaa.getJSONData = function(param) {
			$.getJSON( 
				"slides/" + param,
	//			{_: new Date().getTime()},
				successFn
			)
		.done(function(){
				var $height = $('.slide-1 .tile-lrg .tile-image').height(),
						$container = $('.swiper-container');
				//$height = $height * 2;
				$container.height($height);

				var swiper = new Swiper($container, {
        	nextButton: '.swiper-button-next',
        	prevButton: '.swiper-button-prev',
        	slidesPerView: 'auto',
        	centeredSlides: true,
					spaceBetween: 0,
					loop: true,
					keyboardControl: true,
   			});
  			
//				console.log($height);
		//		$('.tile-tall').each(function(index, value) {
//					$(this).find('.tile-frame').height($height);
//				});
				// init Masonry
	//			var $grid = $('.swiper-slide').masonry({
//				 			itemSelector: '.tile-wrapper',
//				 			columnWidth: '.tile-sizer',
//							percentPosition: true,
//							gutter: 2,  	
//						});
//	
//				$grid.imagesLoaded().progress( function() {
//					$grid.masonry('layout');
//				});				
			});
			
     }

		function successFn(data, status, jqXHR) {
    	if (data.results && data.results.length > 0) {
		//		data.results.reverse();
				var slides = '',
						tiles = [],
						positions = [],
					 	$parentWrapper = $('.swiper-wrapper'),
						wide = [1,9,10,14,20,21,25],
						tall = [4,12,15,23],
						slideBreak = [3,9,14,18,24,29],
						slideStart = [0,4,10,15,21],
						pageNum = 1,
						count = data.results.length,
						counter = 0;
						
						$parentWrapper.html(''); 
						
				$.each(data.results, function(i, node) {
					var tile = '',
							position = '',
							hasImage = node.image || node.imageWide || node.imageTall ? true : false;					
					
					if (i === 0) {
						position = 'tile-lrg';
					}
					else if (jQuery.inArray(i, tall) > -1) {
						position = 'tile-tall';
					}
					else if (jQuery.inArray(i, wide) > -1) {
						position = 'tile-wide';
					}
					else {
						position = 'tile-sm';
					}
					
					if (jQuery.inArray(i, slideStart) > -1) {
						slides += '<div class="swiper-slide slide-' + pageNum + '"><div class="slide-page-inner"><div class="slide-page-content">';
						counter = 0;
					}
					tile += '<div class="tile-wrapper ' + position + ' tile-' + counter +' ' + i +'">';
					
					//tile += '<div class="tile-inner"><div class="tile-frame">';
					tile += node.background ? '<div class="tile-inner bg-' + node.background + '"><div class="tile-frame">' : '<div class="tile-inner"><div class="tile-frame">';
					tile += '<a href="' + node.link +'" target="_blank" class="tile-content">';
					
					
					if (position === 'tile-tall') {
						tile += node.imageTall ? '<div class="tile-image"><img src="' + node.imageTall.src + '" alt="' + node.imageTall.alt + '" /></div>' : '';
					}
					else if(position === 'tile-wide') {
						tile += node.imageWide ? '<div class="tile-image"><img src="' + node.imageWide.src + '" alt="' + node.imageWide.alt + '" /></div>' : '';
					}
					else if (position === 'tile-lrg') {
						tile += node.imageLrg ? '<div class="tile-image"><img src="' + node.imageLrg.src + '" alt="' + node.imageLrg.alt + '" /></div>' : '';
					}
					else {
						tile += node.image ? '<div class="tile-image"><img src="' + node.image.src + '" alt="' + node.image.alt + '" /></div>' : '';
					}
						
	//				if (position === 'tile-tall') {
//						tile += node.imageTall ? '<img class="tile-image" src="' + node.imageTall.src + '" alt="' + node.imageTall.alt + '" />' : '';
//					}
//					else if(position === 'tile-wide') {
//						tile += node.imageWide ? '<img class="tile-image" src="' + node.imageWide.src + '" alt="' + node.imageWide.alt + '" />' : '';
//					}
//					else {
//						tile += node.image ? '<img class="tile-image" src="' + node.image.src + '" alt="' + node.image.alt + '" />' : '';
//					}
//					
					tile += hasImage === true ? '<div class="tile-overlay bg-transparent"></div>' : '<div class="tile-overlay bg-opaque"></div>';
					tile += '<div class="tile-tag">' + node.tag + '</div>';
					tile += '<div class="content-wrapper content-'	+ node.titleState +'">';		 
					tile +=  '<h3 class="tile-title">' + node.title + '</h3>';
					tile += node.caption ? '<div class="tile-caption">' + node.caption + '</div>' : '';										
					tile += '</div></a></div></div></div>';
					
					slides += tile;
					if (jQuery.inArray(i, slideBreak) > -1 || i === (count-1)) {
						slides += '</div></div></div>';
						pageNum++;
					}	
					counter++;	
				});
				//console.log(slides);
				$parentWrapper.html(slides);
			}
    }
	Drupal.si_aaa.searchBox = function(searchDiv) {
		var searchForm = $('form', searchDiv),
				searchField = $('input[type="text"]', searchDiv),
				searchSubmit = $('input:submit', searchDiv);

				searchSubmit.addClass('disabled-state');
				searchField.parent('.form-item').addClass('hidden-state');

		searchDiv.submit(function(event) {
			if(searchSubmit.hasClass('disabled-state')) {
				event.preventDefault();
				searchSubmit.removeClass('disabled-state').addClass('enabled-state');
				searchField.parent('.form-item').removeClass('hidden-state').addClass('visible-state');
			}
			else if(searchSubmit.hasClass('enabled-state')) {
				if(searchField.val().length === 0) {
					event.preventDefault();
					searchSubmit.removeClass('enabled-state').addClass('disabled-state');
					searchField.parent('.form-item').removeClass('visible-state').addClass('hidden-state');
				}
				else {
					return true;
				}
			}

		});
	}

  Drupal.behaviors.si_aaa = {
    attach: function (context, settings) {
					
			var siAAA = siAAA || {};

			siAAA = {
				init : function() {
//					this.layout();
					this.pageInit();
				},
				pageInit : function() {
					// var searchBox = $('.l-header .search-block-form', context),
					// 		searchField = $('input[type="text"]', searchBox),
					// 		searchSubmit = $('input:submit', searchBox);

				//	$('body', context).addClass('js');

					if($('body', context).is(':not(.imce)')) {
						if($('body', context).hasClass('front')) {
							Drupal.si_aaa.getJSONData("all");
							$(".filter").on("click", function () {
								var $this = $(this),
										$parent = $('.swiper-container');	
								// if we click the active tab, do nothing
								if ( !$this.hasClass("active") ) {
										$(".filter").removeClass("active");
										$this.addClass("active"); // set the active tab
										// get the data-rel value from selected tab and set as filter
										var $filter = $this.data("rel");
										Drupal.si_aaa.getJSONData($filter);
										$parent.addClass('filter-' + $filter);
								} // if
							}); // on
						} // end front page
					}
				//	new UISearch( document.getElementById( 'block-search-form' ) );
					//Drupal.si_aaa.searchBox($('.l-header #block-search-form', context));

				},
				layout : function() {
					var winWidth = $(window).width();
         // console.log(winWidth);
					if (winWidth > 680) {
						$('.panel-2col .block--border').matchHeight();
					// 	if (searchBox.is(':not(.processed)')) {
					// 		searchBox.addClass('.processed');
					// 	}
					 }
					 if (winWidth > 979) {
						 var searchID = $('.l-header #block-search-form'),
							   searchContent = searchID.clone();
						 		 tabHeight = $('.l-pane-wrapper.has-bottom-content .r-tabs-panel.r-tabs-state-active').innerHeight() > $('.l-pane-wrapper.has-bottom-content .l-region--bottom').innerHeight() ?
						 $('.l-pane-wrapper.has-bottom-content .r-tabs-panel.r-tabs-state-active').innerHeight() :  $('.l-pane-wrapper.has-bottom-content .l-region--bottom').innerHeight();
						 //console.log(searchID );
						 searchID.remove();
						 $('.l-header-middle .l-region--header').append(searchContent);
						 $('#block-tb-megamenu-menu-social-media .nav-collapse').removeClass('expanded');
						 //Drupal.si_aaa.searchBox($('.l-header-middle .search-block-form'));
						// new UISearch('.l-header #block-search-form');
						 new UISearch( document.getElementById( 'block-search-form' ) );
						// $('.l-pane-wrapper.has-bottom-content > div').matchHeight();
					 }
					else {
						 var searchID = $('.l-header #block-search-form'),
							   searchContent = searchID.clone(),
							 	 //socialMedia = $('#block-menu-menu-social-media', context),
							 	 socialMedia = $('#block-tb-megamenu-menu-social-media', context),
							   socialBtn = $('button', socialMedia);
             // socialBtn.click(function (e) {
             //   $(this).toggleClass('active').parents('.tb-megamenu').toggleClass('expand');
             // });
		        $('button', socialMedia).click(function() {
		          if(parseInt($(this).parent().children('.nav-collapse').height())) {
		          	$(this).addClass('active').parent().children('.nav-collapse').removeClass('collapsed').addClass('expanded');
		            
		          }
		          else {
		            $(this).removeClass('active').parent().children('.nav-collapse').removeClass('expanded').addClass('collapsed');
		          }
		        });             
						 searchID.remove();
						 $('.l-region--header-preface-right').prepend(searchContent);
						 //Drupal.si_aaa.searchBox($('.l-region--header-preface-right .search-block-form'));

						 //new UISearch('.l-header #block-search-form');
						 new UISearch( document.getElementById( 'block-search-form' ) );
					 }

					$('.l-pane-wrapper.has-bottom-content .r-tabs-panel.r-tabs-state-active').height(tabHeight);
					$('.l-pane-wrapper.has-bottom-content .r-tabs-anchor').on("click", function () {
            $('.l-pane-wrapper.has-bottom-content .r-tabs-panel.r-tabs-state-active').height('auto');
						var tabHeight = $('.l-pane-wrapper.has-bottom-content .r-tabs-panel.r-tabs-state-active').innerHeight() > $('.l-pane-wrapper.has-bottom-content .l-region--bottom').innerHeight() ?
							$('.l-pane-wrapper.has-bottom-content .r-tabs-panel.r-tabs-state-active').innerHeight() :  $('.l-pane-wrapper.has-bottom-content .l-region--bottom').innerHeight();
							$('.l-pane-wrapper.has-bottom-content .r-tabs-panel.r-tabs-state-active').height(tabHeight);
					});

				},
			};
			
			siAAA.init();



			// Generic function that runs on window resize.
			function resizeStuff() {
				 siAAA.layout();
			}

			// Runs function once on window resize.
			var TO = false;
			$(window).resize(function () {
				if (TO !== false) {
					clearTimeout(TO);
				}

				// 200 is time in miliseconds.
				TO = setTimeout(resizeStuff, 100);
			}).resize();

      Drupal.si_aaa.splitList($('.split-list ul', context), 2, 'li');
    }
  }

})(jQuery);


