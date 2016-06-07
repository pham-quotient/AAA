
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
	
	  Drupal.si_aaa.getJSONData = function(context, param) {
			$.getJSON( 
				"slides/" + param,
				successFn
			)
			.done(function(){
				var $height = $('.slide-1 .square_lrg .tile-image', context).height(),
						$container = $('.swiper-container', context);
				//$height = $height * 2;
		//		$container.height($heightx);

				var swiper = new Swiper($container, {
        	nextButton: '.swiper-button-next',
        	prevButton: '.swiper-button-prev',
        	slidesPerView: 'auto',
        	centeredSlides: true,
					spaceBetween: 0,
					loop: true
   			});
				
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
				var slides = '',
						tiles = [],
						positions = [],
					 	$parentWrapper = $('.swiper-wrapper');
						$parentWrapper.html(''); 
				$.each(data.results, function(i, node) {
					var tile = '',
							hasImage = node.image || node.imageWide || node.imageTall ? true : false,
							weight = node.weight;
					
					//tile += '<div class="tile-inner"><div class="tile-frame">';
					tile += node.background ? '<div class="tile-inner bg-' + node.background + '"><div class="tile-frame">' : '<div class="tile-inner"><div class="tile-frame">';
					tile += '<a href="' + node.link +'" target="_blank" class="tile-content">';
					
					tile += node.image ? '<div class="tile-image"><img src="' + node.image.src + '" alt="' + node.image.alt + '" /></div>' : '';
					tile += node.imageWide ? '<div class="tile-image"><img src="' + node.imageWide.src + '" alt="' + node.imageWide.alt + '" /></div>' : '';
					tile += node.imageTall ? '<div class="tile-image"><img src="' + node.imageTall.src + '" alt="' + node.imageTall.alt + '" /></div>' : '';
					tile += hasImage === true ? '<div class="tile-overlay bg-transparent"></div>' : '<div class="tile-overlay bg-opaque"></div>';

					tile += '<div class="tile-tag">' + node.tag + '</div>';
					tile += '<div class="content-wrapper content-'	+ node.titleState +'">';		 
					tile +=  '<h3 class="tile-title">' + node.title + '</h3>';
					tile += node.caption ? '<div class="tile-caption">' + node.caption + '</div>' : '';										
					tile += '</div></a></div></div>';
					tiles[i] = tile;
					positions[i] = node.layout;
				});
				tiles.reverse();
				positions.reverse();
				var num = tiles.length,
						counter = 0,
						pageNum = 2;
				num--;
				console.log(positions);
				$.each(tiles, function(j, slide) {
					if (j < 4) {
						slides += j === 0 ?	'<div class="swiper-slide slide-1"><div class="slide-page-inner"><div class="slide-page-content">' : '';
						slides += '<div class="tile-wrapper ' + positions[j] + ' tile-' + j +'">';
						//slides += '<div class="tile-slide;
						slides += slide;
						slides += '</div>';
						slides += j !== 0 && j % 3 === 0 ?	'</div></div></div>' : '';
					}
					else {
						slides += counter === 0 ?	'<div class="swiper-slide slide-' + pageNum + '"><div class="slide-page-inner"><div class="slide-page-content">' : '';
						slides += '<div class="tile-wrapper ' + positions[j] + ' tile-' + counter +'">';
						//slides += '<div class="tile-slide;
						slides += slide;
						slides += '</div>';
						slides += counter === 4 && j !== num  ? '</div></div></div>' : '';
						counter = counter < 4 ? counter+ 1 : 0;
						pageNum = counter === 4 ? pageNum +1 : pageNum;
					}
					console.log(counter);
				});
				slides += '</div></div></div>';
				//console.log(slides);
				$parentWrapper.html(slides);
			}
    }
	
  Drupal.behaviors.si_aaa = {
    attach: function (context, settings) {
			if($('body', context).is(':not(.imce)')) {
				
				Drupal.si_aaa.getJSONData(context, "all");
    		$(".filter").on("click", function () {
        var $this = $(this),
						$parent = $('.swiper-container', context);	
        // if we click the active tab, do nothing
        if ( !$this.hasClass("active") ) {
            $(".filter").removeClass("active");
            $this.addClass("active"); // set the active tab
            // get the data-rel value from selected tab and set as filter
//						$grid.masonry('destroy');
            var $filter = $this.data("rel");
						getJSONData(context, $filter);
						$parent.addClass('filter-' + $filter);
							
						//	 $grid.masonry({
// itemSelector: '.tile-wrapper',
// columnWidth: '.tile-sizer',
// isAnimated: true,
//  // use element for option
//  percentPosition: true,  });	
//							$grid.masonry( 'reloadItems' );
//							$grid.masonry( 'layout' );
        } // if
    }); // on
					
				$(window).setBreakpoints({
					breakpoints: [
							320,
							768,
							980
					] 	
				});
		
		
				$(window).bind('enterBreakpoint980',function() {		
					var	searchID = $('.l-region--header-preface-right .search-link', context);
					
						
					if (searchID.children().is(':not(.processed)')) {
						searchID.children().addClass('processed');
						var searchContent = searchID.html(),
								searchBlock = '<div class="search-link">';
						searchBlock += $.type(searchContent)!== 'undefined' ? searchContent + '</div>' : '</div>';
						$('.l-region--header-wrapper .l-region--header').append(searchBlock);
						searchID.replaceWith(' ');	
					}
					$('.r-tabs-nav .r-tabs-anchor', context).matchHeight({
						byRow: false
					});
					
					
				});
			}
      Drupal.si_aaa.splitList($('.split-list ul', context), 2, 'li');
    }
  }

})(jQuery);


