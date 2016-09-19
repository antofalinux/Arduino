  


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>DHT-sensor-library/DHT.cpp at master · adafruit/DHT-sensor-library · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <link rel="logo" type="image/svg" href="http://github-media-downloads.s3.amazonaws.com/github-logo.svg" />
    <link rel="assets" href="https://a248.e.akamai.net/assets.github.com/">
    <link rel="xhr-socket" href="/_sockets" />
    


    <meta name="msapplication-TileImage" content="/windows-tile.png" />
    <meta name="msapplication-TileColor" content="#ffffff" />
    <meta name="selected-link" value="repo_source" data-pjax-transient />
    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="github" name="octolytics-app-id" />

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="RP/4PSgbiB6orYr71bLUr8+IXQK8lge13ZBtaxD5vcI=" name="csrf-token" />

    <link href="https://a248.e.akamai.net/assets.github.com/assets/github-a4c524f2138ecc4dd5bf9b8a6b1517bf38aa7b65.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://a248.e.akamai.net/assets.github.com/assets/github2-a0dd24a867c60dde11a3c93f5131c4727fe4471a.css" media="all" rel="stylesheet" type="text/css" />
    


      <script src="https://a248.e.akamai.net/assets.github.com/assets/frameworks-5c60c478b1e0f90d149f11ed15aa52edd2996882.js" type="text/javascript"></script>
      <script src="https://a248.e.akamai.net/assets.github.com/assets/github-ec3a88b53ce57e7867078fc6eb817ec0cc60cc9c.js" type="text/javascript"></script>
      
      <meta http-equiv="x-pjax-version" content="25f52f69b20cb47f7b643db402171ea1">

        <link data-pjax-transient rel='permalink' href='/adafruit/DHT-sensor-library/blob/26e2bc1d793fba7f6db41a9f7ce0499b0ab3c622/DHT.cpp'>
    <meta property="og:title" content="DHT-sensor-library"/>
    <meta property="og:type" content="githubog:gitrepository"/>
    <meta property="og:url" content="https://github.com/adafruit/DHT-sensor-library"/>
    <meta property="og:image" content="https://secure.gravatar.com/avatar/4bc2305bba6e4c82a64a8706ae8b3d40?s=420&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png"/>
    <meta property="og:site_name" content="GitHub"/>
    <meta property="og:description" content="DHT-sensor-library - Arduino library for DHT11DHT22, etc Temp &amp; Humidity Sensors"/>
    <meta property="twitter:card" content="summary"/>
    <meta property="twitter:site" content="@GitHub">
    <meta property="twitter:title" content="adafruit/DHT-sensor-library"/>

    <meta name="description" content="DHT-sensor-library - Arduino library for DHT11DHT22, etc Temp &amp; Humidity Sensors" />


    <meta content="181069" name="octolytics-dimension-user_id" /><meta content="adafruit" name="octolytics-dimension-user_login" /><meta content="1926525" name="octolytics-dimension-repository_id" /><meta content="adafruit/DHT-sensor-library" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="1926525" name="octolytics-dimension-repository_network_root_id" /><meta content="adafruit/DHT-sensor-library" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/adafruit/DHT-sensor-library/commits/master.atom" rel="alternate" title="Recent Commits to DHT-sensor-library:master" type="application/atom+xml" />

  </head>


  <body class="logged_out page-blob windows vis-public env-production  ">
    <div id="wrapper">

      
      
      

      
      <div class="header header-logged-out">
  <div class="container clearfix">

    <a class="header-logo-wordmark" href="https://github.com/">Github</a>

    <div class="header-actions">
      <a class="button primary" href="/signup">Sign up</a>
      <a class="button" href="/login?return_to=%2Fadafruit%2FDHT-sensor-library%2Fblob%2Fmaster%2FDHT.cpp">Sign in</a>
    </div>

    <div class="command-bar js-command-bar  in-repository">


      <ul class="top-nav">
          <li class="explore"><a href="/explore">Explore</a></li>
        <li class="features"><a href="/features">Features</a></li>
          <li class="enterprise"><a href="http://enterprise.github.com/">Enterprise</a></li>
          <li class="blog"><a href="/blog">Blog</a></li>
      </ul>
        <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">
  <a href="/search/advanced" class="advanced-search-icon tooltipped downwards command-bar-search" id="advanced_search" title="Advanced search"><span class="octicon octicon-gear "></span></a>

  <input type="text" data-hotkey="/ s" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
      data-repo="adafruit/DHT-sensor-library"
      data-branch="master"
      data-sha="e385397c9ab05be45749eff0e7c796132cbf8364"
  >

    <input type="hidden" name="nwo" value="adafruit/DHT-sensor-library" />

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked" />
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global" />
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="octicon help tooltipped downwards" title="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

  <div class="divider-vertical"></div>

</form>
    </div>

  </div>
</div>


      


            <div class="site hfeed" itemscope itemtype="http://schema.org/WebPage">
      <div class="hentry">
        
        <div class="pagehead repohead instapaper_ignore readability-menu ">
          <div class="container">
            <div class="title-actions-bar">
              

<ul class="pagehead-actions">



    <li>
      <a href="/login?return_to=%2Fadafruit%2FDHT-sensor-library"
        class="minibutton js-toggler-target star-button entice tooltipped upwards"
        title="You must be signed in to use this feature" rel="nofollow">
        <span class="octicon octicon-star"></span>Star
      </a>
      <a class="social-count js-social-count" href="/adafruit/DHT-sensor-library/stargazers">
        115
      </a>
    </li>
    <li>
      <a href="/login?return_to=%2Fadafruit%2FDHT-sensor-library"
        class="minibutton js-toggler-target fork-button entice tooltipped upwards"
        title="You must be signed in to fork a repository" rel="nofollow">
        <span class="octicon octicon-git-branch"></span>Fork
      </a>
      <a href="/adafruit/DHT-sensor-library/network" class="social-count">
        104
      </a>
    </li>
</ul>

              <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
                <span class="repo-label"><span>public</span></span>
                <span class="mega-octicon octicon-repo"></span>
                <span class="author vcard">
                  <a href="/adafruit" class="url fn" itemprop="url" rel="author">
                  <span itemprop="title">adafruit</span>
                  </a></span> /
                <strong><a href="/adafruit/DHT-sensor-library" class="js-current-repository">DHT-sensor-library</a></strong>
              </h1>
            </div>

            
  <ul class="tabs">
    <li class="pulse-nav"><a href="/adafruit/DHT-sensor-library/pulse" class="js-selected-navigation-item " data-selected-links="pulse /adafruit/DHT-sensor-library/pulse" rel="nofollow"><span class="octicon octicon-pulse"></span></a></li>
    <li><a href="/adafruit/DHT-sensor-library" class="js-selected-navigation-item selected" data-selected-links="repo_source repo_downloads repo_commits repo_tags repo_branches /adafruit/DHT-sensor-library">Code</a></li>
    <li><a href="/adafruit/DHT-sensor-library/network" class="js-selected-navigation-item " data-selected-links="repo_network /adafruit/DHT-sensor-library/network">Network</a></li>
    <li><a href="/adafruit/DHT-sensor-library/pulls" class="js-selected-navigation-item " data-selected-links="repo_pulls /adafruit/DHT-sensor-library/pulls">Pull Requests <span class='counter'>2</span></a></li>

      <li><a href="/adafruit/DHT-sensor-library/issues" class="js-selected-navigation-item " data-selected-links="repo_issues /adafruit/DHT-sensor-library/issues">Issues <span class='counter'>4</span></a></li>



    <li><a href="/adafruit/DHT-sensor-library/graphs" class="js-selected-navigation-item " data-selected-links="repo_graphs repo_contributors /adafruit/DHT-sensor-library/graphs">Graphs</a></li>


  </ul>
  
<div class="tabnav">

  <span class="tabnav-right">
    <ul class="tabnav-tabs">
          <li><a href="/adafruit/DHT-sensor-library/tags" class="js-selected-navigation-item tabnav-tab" data-selected-links="repo_tags /adafruit/DHT-sensor-library/tags">Tags <span class="counter blank">0</span></a></li>
    </ul>
  </span>

  <div class="tabnav-widget scope">


    <div class="select-menu js-menu-container js-select-menu js-branch-menu">
      <a class="minibutton select-menu-button js-menu-target" data-hotkey="w" data-ref="master">
        <span class="octicon octicon-git-branch"></span>
        <i>branch:</i>
        <span class="js-select-button">master</span>
      </a>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container">

        <div class="select-menu-modal">
          <div class="select-menu-header">
            <span class="select-menu-title">Switch branches/tags</span>
            <span class="octicon octicon-remove-close js-menu-close"></span>
          </div> <!-- /.select-menu-header -->

          <div class="select-menu-filters">
            <div class="select-menu-text-filter">
              <input type="text" id="commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
            </div>
            <div class="select-menu-tabs">
              <ul>
                <li class="select-menu-tab">
                  <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
                </li>
                <li class="select-menu-tab">
                  <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
                </li>
              </ul>
            </div><!-- /.select-menu-tabs -->
          </div><!-- /.select-menu-filters -->

          <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket css-truncate" data-tab-filter="branches">

            <div data-filterable-for="commitish-filter-field" data-filterable-type="substring">

                <div class="select-menu-item js-navigation-item selected">
                  <span class="select-menu-item-icon octicon octicon-check"></span>
                  <a href="/adafruit/DHT-sensor-library/blob/master/DHT.cpp" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="master" rel="nofollow" title="master">master</a>
                </div> <!-- /.select-menu-item -->
            </div>

              <div class="select-menu-no-results">Nothing to show</div>
          </div> <!-- /.select-menu-list -->


          <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket css-truncate" data-tab-filter="tags">
            <div data-filterable-for="commitish-filter-field" data-filterable-type="substring">

            </div>

            <div class="select-menu-no-results">Nothing to show</div>

          </div> <!-- /.select-menu-list -->

        </div> <!-- /.select-menu-modal -->
      </div> <!-- /.select-menu-modal-holder -->
    </div> <!-- /.select-menu -->

  </div> <!-- /.scope -->

  <ul class="tabnav-tabs">
    <li><a href="/adafruit/DHT-sensor-library" class="selected js-selected-navigation-item tabnav-tab" data-selected-links="repo_source /adafruit/DHT-sensor-library">Files</a></li>
    <li><a href="/adafruit/DHT-sensor-library/commits/master" class="js-selected-navigation-item tabnav-tab" data-selected-links="repo_commits /adafruit/DHT-sensor-library/commits/master">Commits</a></li>
    <li><a href="/adafruit/DHT-sensor-library/branches" class="js-selected-navigation-item tabnav-tab" data-selected-links="repo_branches /adafruit/DHT-sensor-library/branches" rel="nofollow">Branches <span class="counter ">1</span></a></li>
  </ul>

</div>

  
  
  


            
          </div>
        </div><!-- /.repohead -->

        <div id="js-repo-pjax-container" class="container context-loader-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:2d8f6fa730249af9d62e288fd79f47d0 -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:2d8f6fa730249af9d62e288fd79f47d0 -->


<div id="slider">
    <div class="frame-meta">

      <p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

        <div class="breadcrumb">
          <span class='bold'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/adafruit/DHT-sensor-library" class="js-slide-to" data-branch="master" data-direction="back" itemscope="url"><span itemprop="title">DHT-sensor-library</span></a></span></span><span class="separator"> / </span><strong class="final-path">DHT.cpp</strong> <span class="js-zeroclipboard zeroclipboard-button" data-clipboard-text="DHT.cpp" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
        </div>

      <a href="/adafruit/DHT-sensor-library/find/master" class="js-slide-to" data-hotkey="t" style="display:none">Show File Finder</a>


        
  <div class="commit file-history-tease">
    <img class="main-avatar" height="24" src="https://secure.gravatar.com/avatar/32231ca011b84000369f98737e2df96c?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
    <span class="author"><a href="/soerup" rel="author">soerup</a></span>
    <time class="js-relative-date" datetime="2012-12-29T10:14:51-08:00" title="2012-12-29 10:14:51">December 29, 2012</time>
    <div class="commit-title">
        <a href="/adafruit/DHT-sensor-library/commit/ad73fab6233853daa6835212d5a6eb5791e16a3d" class="message">Support for non 16mhz devices</a>
    </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>3</strong> contributors</a></p>
          <a class="avatar tooltipped downwards" title="ladyada" href="/adafruit/DHT-sensor-library/commits/master/DHT.cpp?author=ladyada"><img height="20" src="https://secure.gravatar.com/avatar/3f7ca151e1f7f7dead8b2db60aa744c1?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>
    <a class="avatar tooltipped downwards" title="leprasmurf" href="/adafruit/DHT-sensor-library/commits/master/DHT.cpp?author=leprasmurf"><img height="20" src="https://secure.gravatar.com/avatar/afe5957681fc61f3c1f0fccbfeea5f44?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>
    <a class="avatar tooltipped downwards" title="soerup" href="/adafruit/DHT-sensor-library/commits/master/DHT.cpp?author=soerup"><img height="20" src="https://secure.gravatar.com/avatar/32231ca011b84000369f98737e2df96c?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>


    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2>Users on GitHub who have contributed to this file</h2>
      <ul class="facebox-user-list">
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/3f7ca151e1f7f7dead8b2db60aa744c1?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/ladyada">ladyada</a>
        </li>
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/afe5957681fc61f3c1f0fccbfeea5f44?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/leprasmurf">leprasmurf</a>
        </li>
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/32231ca011b84000369f98737e2df96c?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/soerup">soerup</a>
        </li>
      </ul>
    </div>
  </div>


    </div><!-- ./.frame-meta -->

    <div class="frames">
      <div class="frame" data-permalink-url="/adafruit/DHT-sensor-library/blob/26e2bc1d793fba7f6db41a9f7ce0499b0ab3c622/DHT.cpp" data-title="DHT-sensor-library/DHT.cpp at master · adafruit/DHT-sensor-library · GitHub" data-type="blob">

        <div id="files" class="bubble">
          <div class="file">
            <div class="meta">
              <div class="info">
                <span class="icon"><b class="octicon octicon-file-text"></b></span>
                <span class="mode" title="File Mode">file</span>
                  <span>162 lines (135 sloc)</span>
                <span>3.197 kb</span>
              </div>
              <div class="actions">
                <div class="button-group">
                      <a class="minibutton js-entice" href=""
                         data-entice="You must be signed in and on a branch to make or propose changes">Edit</a>
                  <a href="/adafruit/DHT-sensor-library/raw/master/DHT.cpp" class="button minibutton " id="raw-url">Raw</a>
                    <a href="/adafruit/DHT-sensor-library/blame/master/DHT.cpp" class="button minibutton ">Blame</a>
                  <a href="/adafruit/DHT-sensor-library/commits/master/DHT.cpp" class="button minibutton " rel="nofollow">History</a>
                </div><!-- /.button-group -->
              </div><!-- /.actions -->

            </div>
                <div class="blob-wrapper data type-c js-blob-data">
      <table class="file-code file-diff">
        <tr class="file-code-line">
          <td class="blob-line-nums">
            <span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>
<span id="L146" rel="#L146">146</span>
<span id="L147" rel="#L147">147</span>
<span id="L148" rel="#L148">148</span>
<span id="L149" rel="#L149">149</span>
<span id="L150" rel="#L150">150</span>
<span id="L151" rel="#L151">151</span>
<span id="L152" rel="#L152">152</span>
<span id="L153" rel="#L153">153</span>
<span id="L154" rel="#L154">154</span>
<span id="L155" rel="#L155">155</span>
<span id="L156" rel="#L156">156</span>
<span id="L157" rel="#L157">157</span>
<span id="L158" rel="#L158">158</span>
<span id="L159" rel="#L159">159</span>
<span id="L160" rel="#L160">160</span>
<span id="L161" rel="#L161">161</span>

          </td>
          <td class="blob-line-code">
                  <div class="highlight"><pre><div class='line' id='LC1'><span class="cm">/* DHT library </span></div><div class='line' id='LC2'><br/></div><div class='line' id='LC3'><span class="cm">MIT license</span></div><div class='line' id='LC4'><span class="cm">written by Adafruit Industries</span></div><div class='line' id='LC5'><span class="cm">*/</span></div><div class='line' id='LC6'><br/></div><div class='line' id='LC7'><span class="cp">#include &quot;DHT.h&quot;</span></div><div class='line' id='LC8'><br/></div><div class='line' id='LC9'><span class="n">DHT</span><span class="o">::</span><span class="n">DHT</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">pin</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">type</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">count</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC10'>&nbsp;&nbsp;<span class="n">_pin</span> <span class="o">=</span> <span class="n">pin</span><span class="p">;</span></div><div class='line' id='LC11'>&nbsp;&nbsp;<span class="n">_type</span> <span class="o">=</span> <span class="n">type</span><span class="p">;</span></div><div class='line' id='LC12'>&nbsp;&nbsp;<span class="n">_count</span> <span class="o">=</span> <span class="n">count</span><span class="p">;</span></div><div class='line' id='LC13'>&nbsp;&nbsp;<span class="n">firstreading</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC14'><span class="p">}</span></div><div class='line' id='LC15'><br/></div><div class='line' id='LC16'><span class="kt">void</span> <span class="n">DHT</span><span class="o">::</span><span class="n">begin</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC17'>&nbsp;&nbsp;<span class="c1">// set up the pins!</span></div><div class='line' id='LC18'>&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">_pin</span><span class="p">,</span> <span class="n">INPUT</span><span class="p">);</span></div><div class='line' id='LC19'>&nbsp;&nbsp;<span class="n">digitalWrite</span><span class="p">(</span><span class="n">_pin</span><span class="p">,</span> <span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC20'>&nbsp;&nbsp;<span class="n">_lastreadtime</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC21'><span class="p">}</span></div><div class='line' id='LC22'><br/></div><div class='line' id='LC23'><span class="c1">//boolean S == Scale.  True == Farenheit; False == Celcius</span></div><div class='line' id='LC24'><span class="kt">float</span> <span class="n">DHT</span><span class="o">::</span><span class="n">readTemperature</span><span class="p">(</span><span class="kt">bool</span> <span class="n">S</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC25'>&nbsp;&nbsp;<span class="kt">float</span> <span class="n">f</span><span class="p">;</span></div><div class='line' id='LC26'><br/></div><div class='line' id='LC27'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">read</span><span class="p">())</span> <span class="p">{</span></div><div class='line' id='LC28'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">switch</span> <span class="p">(</span><span class="n">_type</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC29'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">DHT11</span>:</div><div class='line' id='LC30'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">=</span> <span class="n">data</span><span class="p">[</span><span class="mi">2</span><span class="p">];</span></div><div class='line' id='LC31'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">S</span><span class="p">)</span></div><div class='line' id='LC32'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	<span class="n">f</span> <span class="o">=</span> <span class="n">convertCtoF</span><span class="p">(</span><span class="n">f</span><span class="p">);</span></div><div class='line' id='LC33'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	</div><div class='line' id='LC34'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">f</span><span class="p">;</span></div><div class='line' id='LC35'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">DHT22</span>:</div><div class='line' id='LC36'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">DHT21</span>:</div><div class='line' id='LC37'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">=</span> <span class="n">data</span><span class="p">[</span><span class="mi">2</span><span class="p">]</span> <span class="o">&amp;</span> <span class="mh">0x7F</span><span class="p">;</span></div><div class='line' id='LC38'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">*=</span> <span class="mi">256</span><span class="p">;</span></div><div class='line' id='LC39'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">+=</span> <span class="n">data</span><span class="p">[</span><span class="mi">3</span><span class="p">];</span></div><div class='line' id='LC40'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">/=</span> <span class="mi">10</span><span class="p">;</span></div><div class='line' id='LC41'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">data</span><span class="p">[</span><span class="mi">2</span><span class="p">]</span> <span class="o">&amp;</span> <span class="mh">0x80</span><span class="p">)</span></div><div class='line' id='LC42'>	<span class="n">f</span> <span class="o">*=</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC43'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">S</span><span class="p">)</span></div><div class='line' id='LC44'>	<span class="n">f</span> <span class="o">=</span> <span class="n">convertCtoF</span><span class="p">(</span><span class="n">f</span><span class="p">);</span></div><div class='line' id='LC45'><br/></div><div class='line' id='LC46'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">f</span><span class="p">;</span></div><div class='line' id='LC47'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC48'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC49'>&nbsp;&nbsp;<span class="n">Serial</span><span class="p">.</span><span class="n">print</span><span class="p">(</span><span class="s">&quot;Read fail&quot;</span><span class="p">);</span></div><div class='line' id='LC50'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">NAN</span><span class="p">;</span></div><div class='line' id='LC51'><span class="p">}</span></div><div class='line' id='LC52'><br/></div><div class='line' id='LC53'><span class="kt">float</span> <span class="n">DHT</span><span class="o">::</span><span class="n">convertCtoF</span><span class="p">(</span><span class="kt">float</span> <span class="n">c</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC54'>	<span class="k">return</span> <span class="n">c</span> <span class="o">*</span> <span class="mi">9</span> <span class="o">/</span> <span class="mi">5</span> <span class="o">+</span> <span class="mi">32</span><span class="p">;</span></div><div class='line' id='LC55'><span class="p">}</span></div><div class='line' id='LC56'><br/></div><div class='line' id='LC57'><span class="kt">float</span> <span class="n">DHT</span><span class="o">::</span><span class="n">readHumidity</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC58'>&nbsp;&nbsp;<span class="kt">float</span> <span class="n">f</span><span class="p">;</span></div><div class='line' id='LC59'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">read</span><span class="p">())</span> <span class="p">{</span></div><div class='line' id='LC60'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">switch</span> <span class="p">(</span><span class="n">_type</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC61'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">DHT11</span>:</div><div class='line' id='LC62'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">=</span> <span class="n">data</span><span class="p">[</span><span class="mi">0</span><span class="p">];</span></div><div class='line' id='LC63'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">f</span><span class="p">;</span></div><div class='line' id='LC64'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">DHT22</span>:</div><div class='line' id='LC65'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">DHT21</span>:</div><div class='line' id='LC66'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">=</span> <span class="n">data</span><span class="p">[</span><span class="mi">0</span><span class="p">];</span></div><div class='line' id='LC67'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">*=</span> <span class="mi">256</span><span class="p">;</span></div><div class='line' id='LC68'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">+=</span> <span class="n">data</span><span class="p">[</span><span class="mi">1</span><span class="p">];</span></div><div class='line' id='LC69'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">f</span> <span class="o">/=</span> <span class="mi">10</span><span class="p">;</span></div><div class='line' id='LC70'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">f</span><span class="p">;</span></div><div class='line' id='LC71'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC72'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC73'>&nbsp;&nbsp;<span class="n">Serial</span><span class="p">.</span><span class="n">print</span><span class="p">(</span><span class="s">&quot;Read fail&quot;</span><span class="p">);</span></div><div class='line' id='LC74'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">NAN</span><span class="p">;</span></div><div class='line' id='LC75'><span class="p">}</span></div><div class='line' id='LC76'><br/></div><div class='line' id='LC77'><br/></div><div class='line' id='LC78'><span class="n">boolean</span> <span class="n">DHT</span><span class="o">::</span><span class="n">read</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC79'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">laststate</span> <span class="o">=</span> <span class="n">HIGH</span><span class="p">;</span></div><div class='line' id='LC80'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">counter</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC81'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="n">j</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">i</span><span class="p">;</span></div><div class='line' id='LC82'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">currenttime</span><span class="p">;</span></div><div class='line' id='LC83'><br/></div><div class='line' id='LC84'>&nbsp;&nbsp;<span class="c1">// pull the pin high and wait 250 milliseconds</span></div><div class='line' id='LC85'>&nbsp;&nbsp;<span class="n">digitalWrite</span><span class="p">(</span><span class="n">_pin</span><span class="p">,</span> <span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC86'>&nbsp;&nbsp;<span class="n">delay</span><span class="p">(</span><span class="mi">250</span><span class="p">);</span></div><div class='line' id='LC87'><br/></div><div class='line' id='LC88'>&nbsp;&nbsp;<span class="n">currenttime</span> <span class="o">=</span> <span class="n">millis</span><span class="p">();</span></div><div class='line' id='LC89'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">currenttime</span> <span class="o">&lt;</span> <span class="n">_lastreadtime</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC90'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// ie there was a rollover</span></div><div class='line' id='LC91'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">_lastreadtime</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC92'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC93'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="n">firstreading</span> <span class="o">&amp;&amp;</span> <span class="p">((</span><span class="n">currenttime</span> <span class="o">-</span> <span class="n">_lastreadtime</span><span class="p">)</span> <span class="o">&lt;</span> <span class="mi">2000</span><span class="p">))</span> <span class="p">{</span></div><div class='line' id='LC94'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="nb">true</span><span class="p">;</span> <span class="c1">// return last correct measurement</span></div><div class='line' id='LC95'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//delay(2000 - (currenttime - _lastreadtime));</span></div><div class='line' id='LC96'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC97'>&nbsp;&nbsp;<span class="n">firstreading</span> <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC98'>&nbsp;&nbsp;<span class="cm">/*</span></div><div class='line' id='LC99'><span class="cm">    Serial.print(&quot;Currtime: &quot;); Serial.print(currenttime);</span></div><div class='line' id='LC100'><span class="cm">    Serial.print(&quot; Lasttime: &quot;); Serial.print(_lastreadtime);</span></div><div class='line' id='LC101'><span class="cm">  */</span></div><div class='line' id='LC102'>&nbsp;&nbsp;<span class="n">_lastreadtime</span> <span class="o">=</span> <span class="n">millis</span><span class="p">();</span></div><div class='line' id='LC103'><br/></div><div class='line' id='LC104'>&nbsp;&nbsp;<span class="n">data</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span> <span class="o">=</span> <span class="n">data</span><span class="p">[</span><span class="mi">1</span><span class="p">]</span> <span class="o">=</span> <span class="n">data</span><span class="p">[</span><span class="mi">2</span><span class="p">]</span> <span class="o">=</span> <span class="n">data</span><span class="p">[</span><span class="mi">3</span><span class="p">]</span> <span class="o">=</span> <span class="n">data</span><span class="p">[</span><span class="mi">4</span><span class="p">]</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC105'>&nbsp;&nbsp;</div><div class='line' id='LC106'>&nbsp;&nbsp;<span class="c1">// now pull it low for ~20 milliseconds</span></div><div class='line' id='LC107'>&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">_pin</span><span class="p">,</span> <span class="n">OUTPUT</span><span class="p">);</span></div><div class='line' id='LC108'>&nbsp;&nbsp;<span class="n">digitalWrite</span><span class="p">(</span><span class="n">_pin</span><span class="p">,</span> <span class="n">LOW</span><span class="p">);</span></div><div class='line' id='LC109'>&nbsp;&nbsp;<span class="n">delay</span><span class="p">(</span><span class="mi">20</span><span class="p">);</span></div><div class='line' id='LC110'>&nbsp;&nbsp;<span class="n">cli</span><span class="p">();</span></div><div class='line' id='LC111'>&nbsp;&nbsp;<span class="n">digitalWrite</span><span class="p">(</span><span class="n">_pin</span><span class="p">,</span> <span class="n">HIGH</span><span class="p">);</span></div><div class='line' id='LC112'>&nbsp;&nbsp;<span class="n">delayMicroseconds</span><span class="p">(</span><span class="mi">40</span><span class="p">);</span></div><div class='line' id='LC113'>&nbsp;&nbsp;<span class="n">pinMode</span><span class="p">(</span><span class="n">_pin</span><span class="p">,</span> <span class="n">INPUT</span><span class="p">);</span></div><div class='line' id='LC114'><br/></div><div class='line' id='LC115'>&nbsp;&nbsp;<span class="c1">// read in timings</span></div><div class='line' id='LC116'>&nbsp;&nbsp;<span class="k">for</span> <span class="p">(</span> <span class="n">i</span><span class="o">=</span><span class="mi">0</span><span class="p">;</span> <span class="n">i</span><span class="o">&lt;</span> <span class="n">MAXTIMINGS</span><span class="p">;</span> <span class="n">i</span><span class="o">++</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC117'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">counter</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC118'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="n">digitalRead</span><span class="p">(</span><span class="n">_pin</span><span class="p">)</span> <span class="o">==</span> <span class="n">laststate</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC119'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">counter</span><span class="o">++</span><span class="p">;</span></div><div class='line' id='LC120'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">delayMicroseconds</span><span class="p">(</span><span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC121'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">counter</span> <span class="o">==</span> <span class="mi">255</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC122'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC123'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC124'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC125'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">laststate</span> <span class="o">=</span> <span class="n">digitalRead</span><span class="p">(</span><span class="n">_pin</span><span class="p">);</span></div><div class='line' id='LC126'><br/></div><div class='line' id='LC127'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">counter</span> <span class="o">==</span> <span class="mi">255</span><span class="p">)</span> <span class="k">break</span><span class="p">;</span></div><div class='line' id='LC128'><br/></div><div class='line' id='LC129'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// ignore first 3 transitions</span></div><div class='line' id='LC130'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">((</span><span class="n">i</span> <span class="o">&gt;=</span> <span class="mi">4</span><span class="p">)</span> <span class="o">&amp;&amp;</span> <span class="p">(</span><span class="n">i</span><span class="o">%</span><span class="mi">2</span> <span class="o">==</span> <span class="mi">0</span><span class="p">))</span> <span class="p">{</span></div><div class='line' id='LC131'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// shove each bit into the storage bytes</span></div><div class='line' id='LC132'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">data</span><span class="p">[</span><span class="n">j</span><span class="o">/</span><span class="mi">8</span><span class="p">]</span> <span class="o">&lt;&lt;=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC133'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">counter</span> <span class="o">&gt;</span> <span class="n">_count</span><span class="p">)</span></div><div class='line' id='LC134'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">data</span><span class="p">[</span><span class="n">j</span><span class="o">/</span><span class="mi">8</span><span class="p">]</span> <span class="o">|=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC135'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">j</span><span class="o">++</span><span class="p">;</span></div><div class='line' id='LC136'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC137'><br/></div><div class='line' id='LC138'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC139'><br/></div><div class='line' id='LC140'>&nbsp;&nbsp;<span class="n">sei</span><span class="p">();</span></div><div class='line' id='LC141'>&nbsp;&nbsp;</div><div class='line' id='LC142'>&nbsp;&nbsp;<span class="cm">/*</span></div><div class='line' id='LC143'><span class="cm">  Serial.println(j, DEC);</span></div><div class='line' id='LC144'><span class="cm">  Serial.print(data[0], HEX); Serial.print(&quot;, &quot;);</span></div><div class='line' id='LC145'><span class="cm">  Serial.print(data[1], HEX); Serial.print(&quot;, &quot;);</span></div><div class='line' id='LC146'><span class="cm">  Serial.print(data[2], HEX); Serial.print(&quot;, &quot;);</span></div><div class='line' id='LC147'><span class="cm">  Serial.print(data[3], HEX); Serial.print(&quot;, &quot;);</span></div><div class='line' id='LC148'><span class="cm">  Serial.print(data[4], HEX); Serial.print(&quot; =? &quot;);</span></div><div class='line' id='LC149'><span class="cm">  Serial.println(data[0] + data[1] + data[2] + data[3], HEX);</span></div><div class='line' id='LC150'><span class="cm">  */</span></div><div class='line' id='LC151'><br/></div><div class='line' id='LC152'>&nbsp;&nbsp;<span class="c1">// check we read 40 bits and that the checksum matches</span></div><div class='line' id='LC153'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">((</span><span class="n">j</span> <span class="o">&gt;=</span> <span class="mi">40</span><span class="p">)</span> <span class="o">&amp;&amp;</span> </div><div class='line' id='LC154'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">data</span><span class="p">[</span><span class="mi">4</span><span class="p">]</span> <span class="o">==</span> <span class="p">((</span><span class="n">data</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span> <span class="o">+</span> <span class="n">data</span><span class="p">[</span><span class="mi">1</span><span class="p">]</span> <span class="o">+</span> <span class="n">data</span><span class="p">[</span><span class="mi">2</span><span class="p">]</span> <span class="o">+</span> <span class="n">data</span><span class="p">[</span><span class="mi">3</span><span class="p">])</span> <span class="o">&amp;</span> <span class="mh">0xFF</span><span class="p">))</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC155'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC156'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC157'>&nbsp;&nbsp;</div><div class='line' id='LC158'><br/></div><div class='line' id='LC159'>&nbsp;&nbsp;<span class="k">return</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC160'><br/></div><div class='line' id='LC161'><span class="p">}</span></div></pre></div>
          </td>
        </tr>
      </table>
  </div>

          </div>
        </div>

        <a href="#jump-to-line" rel="facebox" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
        <div id="jump-to-line" style="display:none">
          <h2>Jump to Line</h2>
          <form accept-charset="UTF-8" class="js-jump-to-line-form">
            <input class="textfield js-jump-to-line-field" type="text">
            <div class="full-button">
              <button type="submit" class="button">Go</button>
            </div>
          </form>
        </div>

      </div>
    </div>
</div>

<div id="js-frame-loading-template" class="frame frame-loading large-loading-area" style="display:none;">
  <img class="js-frame-loading-spinner" src="https://a248.e.akamai.net/assets.github.com/images/spinners/octocat-spinner-128.gif" height="64" width="64">
</div>


        </div>
      </div>
      <div class="modal-backdrop"></div>
    </div>

      <div id="footer-push"></div><!-- hack for sticky footer -->
    </div><!-- end of wrapper - hack for sticky footer -->

      <!-- footer -->
      <div id="footer">
  <div class="container clearfix">

      <dl class="footer_nav">
        <dt>GitHub</dt>
        <dd><a href="/about">About us</a></dd>
        <dd><a href="/blog">Blog</a></dd>
        <dd><a href="/contact">Contact &amp; support</a></dd>
        <dd><a href="http://enterprise.github.com/">GitHub Enterprise</a></dd>
        <dd><a href="http://status.github.com/">Site status</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Applications</dt>
        <dd><a href="http://mac.github.com/">GitHub for Mac</a></dd>
        <dd><a href="http://windows.github.com/">GitHub for Windows</a></dd>
        <dd><a href="http://eclipse.github.com/">GitHub for Eclipse</a></dd>
        <dd><a href="http://mobile.github.com/">GitHub mobile apps</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Services</dt>
        <dd><a href="http://get.gaug.es/">Gauges: Web analytics</a></dd>
        <dd><a href="http://speakerdeck.com">Speaker Deck: Presentations</a></dd>
        <dd><a href="https://gist.github.com">Gist: Code snippets</a></dd>
        <dd><a href="http://jobs.github.com/">Job board</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Documentation</dt>
        <dd><a href="http://help.github.com/">GitHub Help</a></dd>
        <dd><a href="http://developer.github.com/">Developer API</a></dd>
        <dd><a href="http://github.github.com/github-flavored-markdown/">GitHub Flavored Markdown</a></dd>
        <dd><a href="http://pages.github.com/">GitHub Pages</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>More</dt>
        <dd><a href="http://training.github.com/">Training</a></dd>
        <dd><a href="/edu">Students &amp; teachers</a></dd>
        <dd><a href="http://shop.github.com">The Shop</a></dd>
        <dd><a href="/plans">Plans &amp; pricing</a></dd>
        <dd><a href="http://octodex.github.com/">The Octodex</a></dd>
      </dl>

      <hr class="footer-divider">


    <p class="right">&copy; 2013 <span title="0.03755s from fe4.rs.github.com">GitHub</span>, Inc. All rights reserved.</p>
    <a class="left" href="/">
      <span class="mega-octicon octicon-mark-github"></span>
    </a>
    <ul id="legal">
        <li><a href="/site/terms">Terms of Service</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
    </ul>

  </div><!-- /.container -->

</div><!-- /.#footer -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
          <div class="suggester-container">
              <div class="suggester fullscreen-suggester js-navigation-container" id="fullscreen_suggester"
                 data-url="/adafruit/DHT-sensor-library/suggestions/commit">
              </div>
          </div>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped leftwards" title="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped leftwards"
      title="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      Something went wrong with that request. Please try again.
      <a href="#" class="octicon octicon-remove-close ajax-error-dismiss"></a>
    </div>

    
    <span id='server_response_time' data-time='0.03783' data-host='fe4'></span>
    
  </body>
</html>

