  


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>DHT-sensor-library/examples/DHTtester/DHTtester.pde at master · adafruit/DHT-sensor-library · GitHub</title>
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

        <link data-pjax-transient rel='permalink' href='/adafruit/DHT-sensor-library/blob/26e2bc1d793fba7f6db41a9f7ce0499b0ab3c622/examples/DHTtester/DHTtester.pde'>
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
      <a class="button" href="/login?return_to=%2Fadafruit%2FDHT-sensor-library%2Fblob%2Fmaster%2Fexamples%2FDHTtester%2FDHTtester.pde">Sign in</a>
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
                  <a href="/adafruit/DHT-sensor-library/blob/master/examples/DHTtester/DHTtester.pde" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="master" rel="nofollow" title="master">master</a>
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
          


<!-- blob contrib key: blob_contributors:v21:65f1ca90807511a8409243bca4fb952f -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:65f1ca90807511a8409243bca4fb952f -->


<div id="slider">
    <div class="frame-meta">

      <p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

        <div class="breadcrumb">
          <span class='bold'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/adafruit/DHT-sensor-library" class="js-slide-to" data-branch="master" data-direction="back" itemscope="url"><span itemprop="title">DHT-sensor-library</span></a></span></span><span class="separator"> / </span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/adafruit/DHT-sensor-library/tree/master/examples" class="js-slide-to" data-branch="master" data-direction="back" itemscope="url"><span itemprop="title">examples</span></a></span><span class="separator"> / </span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/adafruit/DHT-sensor-library/tree/master/examples/DHTtester" class="js-slide-to" data-branch="master" data-direction="back" itemscope="url"><span itemprop="title">DHTtester</span></a></span><span class="separator"> / </span><strong class="final-path">DHTtester.pde</strong> <span class="js-zeroclipboard zeroclipboard-button" data-clipboard-text="examples/DHTtester/DHTtester.pde" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
        </div>

      <a href="/adafruit/DHT-sensor-library/find/master" class="js-slide-to" data-hotkey="t" style="display:none">Show File Finder</a>


        
  <div class="commit file-history-tease">
    <img class="main-avatar" height="24" src="https://secure.gravatar.com/avatar/3f7ca151e1f7f7dead8b2db60aa744c1?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
    <span class="author"><a href="/ladyada" rel="author">ladyada</a></span>
    <time class="js-relative-date" datetime="2011-06-22T13:28:22-07:00" title="2011-06-22 13:28:22">June 22, 2011</time>
    <div class="commit-title">
        <a href="/adafruit/DHT-sensor-library/commit/31b6b4535204d168eea31d6034b66be42e1cfb55" class="message">clarified the pullup</a>
    </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>1</strong> contributor</a></p>
      
    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2>Users on GitHub who have contributed to this file</h2>
      <ul class="facebox-user-list">
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/3f7ca151e1f7f7dead8b2db60aa744c1?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/ladyada">ladyada</a>
        </li>
      </ul>
    </div>
  </div>


    </div><!-- ./.frame-meta -->

    <div class="frames">
      <div class="frame" data-permalink-url="/adafruit/DHT-sensor-library/blob/26e2bc1d793fba7f6db41a9f7ce0499b0ab3c622/examples/DHTtester/DHTtester.pde" data-title="DHT-sensor-library/examples/DHTtester/DHTtester.pde at master · adafruit/DHT-sensor-library · GitHub" data-type="blob">

        <div id="files" class="bubble">
          <div class="file">
            <div class="meta">
              <div class="info">
                <span class="icon"><b class="octicon octicon-file-text"></b></span>
                <span class="mode" title="File Mode">file</span>
                  <span>45 lines (35 sloc)</span>
                <span>1.286 kb</span>
              </div>
              <div class="actions">
                <div class="button-group">
                      <a class="minibutton js-entice" href=""
                         data-entice="You must be signed in and on a branch to make or propose changes">Edit</a>
                  <a href="/adafruit/DHT-sensor-library/raw/master/examples/DHTtester/DHTtester.pde" class="button minibutton " id="raw-url">Raw</a>
                    <a href="/adafruit/DHT-sensor-library/blame/master/examples/DHTtester/DHTtester.pde" class="button minibutton ">Blame</a>
                  <a href="/adafruit/DHT-sensor-library/commits/master/examples/DHTtester/DHTtester.pde" class="button minibutton " rel="nofollow">History</a>
                </div><!-- /.button-group -->
              </div><!-- /.actions -->

            </div>
                <div class="blob-wrapper data type-processing js-blob-data">
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

          </td>
          <td class="blob-line-code">
                  <div class="highlight"><pre><div class='line' id='LC1'><span class="c1">// Example testing sketch for various DHT humidity/temperature sensors</span></div><div class='line' id='LC2'><span class="c1">// Written by ladyada, public domain</span></div><div class='line' id='LC3'><br/></div><div class='line' id='LC4'><span class="err">#</span><span class="n">include</span> <span class="s">&quot;DHT.h&quot;</span></div><div class='line' id='LC5'><br/></div><div class='line' id='LC6'><span class="err">#</span><span class="n">define</span> <span class="n">DHTPIN</span> <span class="mi">2</span>     <span class="c1">// what pin we&#39;re connected to</span></div><div class='line' id='LC7'><br/></div><div class='line' id='LC8'><span class="c1">// Uncomment whatever type you&#39;re using!</span></div><div class='line' id='LC9'><span class="c1">//#define DHTTYPE DHT11   // DHT 11 </span></div><div class='line' id='LC10'><span class="err">#</span><span class="n">define</span> <span class="n">DHTTYPE</span> <span class="n">DHT22</span>   <span class="c1">// DHT 22  (AM2302)</span></div><div class='line' id='LC11'><span class="c1">//#define DHTTYPE DHT21   // DHT 21 (AM2301)</span></div><div class='line' id='LC12'><br/></div><div class='line' id='LC13'><span class="c1">// Connect pin 1 (on the left) of the sensor to +5V</span></div><div class='line' id='LC14'><span class="c1">// Connect pin 2 of the sensor to whatever your DHTPIN is</span></div><div class='line' id='LC15'><span class="c1">// Connect pin 4 (on the right) of the sensor to GROUND</span></div><div class='line' id='LC16'><span class="c1">// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor</span></div><div class='line' id='LC17'><br/></div><div class='line' id='LC18'><span class="n">DHT</span> <span class="nf">dht</span><span class="o">(</span><span class="n">DHTPIN</span><span class="o">,</span> <span class="n">DHTTYPE</span><span class="o">);</span></div><div class='line' id='LC19'><br/></div><div class='line' id='LC20'><span class="kt">void</span> <span class="nf">setup</span><span class="o">()</span> <span class="o">{</span></div><div class='line' id='LC21'>&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">begin</span><span class="o">(</span><span class="mi">9600</span><span class="o">);</span> </div><div class='line' id='LC22'>&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">println</span><span class="o">(</span><span class="s">&quot;DHTxx test!&quot;</span><span class="o">);</span></div><div class='line' id='LC23'>&nbsp;</div><div class='line' id='LC24'>&nbsp;&nbsp;<span class="n">dht</span><span class="o">.</span><span class="na">begin</span><span class="o">();</span></div><div class='line' id='LC25'><span class="o">}</span></div><div class='line' id='LC26'><br/></div><div class='line' id='LC27'><span class="kt">void</span> <span class="nf">loop</span><span class="o">()</span> <span class="o">{</span></div><div class='line' id='LC28'>&nbsp;&nbsp;<span class="c1">// Reading temperature or humidity takes about 250 milliseconds!</span></div><div class='line' id='LC29'>&nbsp;&nbsp;<span class="c1">// Sensor readings may also be up to 2 seconds &#39;old&#39; (its a very slow sensor)</span></div><div class='line' id='LC30'>&nbsp;&nbsp;<span class="kt">float</span> <span class="n">h</span> <span class="o">=</span> <span class="n">dht</span><span class="o">.</span><span class="na">readHumidity</span><span class="o">();</span></div><div class='line' id='LC31'>&nbsp;&nbsp;<span class="kt">float</span> <span class="n">t</span> <span class="o">=</span> <span class="n">dht</span><span class="o">.</span><span class="na">readTemperature</span><span class="o">();</span></div><div class='line' id='LC32'><br/></div><div class='line' id='LC33'>&nbsp;&nbsp;<span class="c1">// check if returns are valid, if they are NaN (not a number) then something went wrong!</span></div><div class='line' id='LC34'>&nbsp;&nbsp;<span class="k">if</span> <span class="o">(</span><span class="n">isnan</span><span class="o">(</span><span class="n">t</span><span class="o">)</span> <span class="o">||</span> <span class="n">isnan</span><span class="o">(</span><span class="n">h</span><span class="o">))</span> <span class="o">{</span></div><div class='line' id='LC35'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">println</span><span class="o">(</span><span class="s">&quot;Failed to read from DHT&quot;</span><span class="o">);</span></div><div class='line' id='LC36'>&nbsp;&nbsp;<span class="o">}</span> <span class="k">else</span> <span class="o">{</span></div><div class='line' id='LC37'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">print</span><span class="o">(</span><span class="s">&quot;Humidity: &quot;</span><span class="o">);</span> </div><div class='line' id='LC38'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">print</span><span class="o">(</span><span class="n">h</span><span class="o">);</span></div><div class='line' id='LC39'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">print</span><span class="o">(</span><span class="s">&quot; %\t&quot;</span><span class="o">);</span></div><div class='line' id='LC40'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">print</span><span class="o">(</span><span class="s">&quot;Temperature: &quot;</span><span class="o">);</span> </div><div class='line' id='LC41'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">print</span><span class="o">(</span><span class="n">t</span><span class="o">);</span></div><div class='line' id='LC42'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">Serial</span><span class="o">.</span><span class="na">println</span><span class="o">(</span><span class="s">&quot; *C&quot;</span><span class="o">);</span></div><div class='line' id='LC43'>&nbsp;&nbsp;<span class="o">}</span></div><div class='line' id='LC44'><span class="o">}</span></div></pre></div>
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


    <p class="right">&copy; 2013 <span title="0.03939s from fe4.rs.github.com">GitHub</span>, Inc. All rights reserved.</p>
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

    
    <span id='server_response_time' data-time='0.03970' data-host='fe4'></span>
    
  </body>
</html>

