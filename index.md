---
title: "KPIT APEX Lab: Linux Assignment Page"
layout: default
---

{%- comment -%}
Pre-render the root-level Markdown files using Liquid + markdownify.
This ensures RIGHT PANE always shows proper, styled HTML (not raw .md).
{%- endcomment -%}
{%- capture MD_SIGNAL -%}{% include_relative signal.md %}{%- endcapture -%}
{%- capture MD_THREAD -%}{% include_relative thread.md %}{%- endcapture -%}
{%- capture MD_PIPE   -%}{% include_relative posixpipe.md %}{%- endcapture -%}
{%- capture MD_FIFO   -%}{% include_relative posixfifo.md %}{%- endcapture -%}
{%- capture MD_SHM    -%}{% include_relative posixshm.md %}{%- endcapture -%}
{%- capture MD_MQUEUE -%}{% include_relative posixmsgque.md %}{%- endcapture -%}

<style>
/* ============== FORCE FULL-WIDTH (override GitHub Pages wrappers) ============== */
html, body { width: 100% !important; margin: 0 !important; padding: 0 !important; }
.wrapper, .page, .page-content, .main-content, .markdown-body,
.container, .container-lg, .container-xl, .px-3, div[role="main"], main {
  max-width: none !important; width: 100% !important; margin: 0 !important; padding: 0 !important;
}

/* ============== HIDE THEME CHROME ON THIS PAGE ============== */
.page-header, .site-header, header,
.site-footer, footer,
a.btn[href*="github.com"], a[href*="github.com"].btn { display: none !important; }

/* ============== LAYOUT: header + 20/80 grid ============== */
#apex-wrap { padding: 0; }
#apex-title { margin: 12px 0 14px 12px; font-size: 1.8rem; font-weight: 800; color: #0f172a; }
#apex-grid  { display: grid; grid-template-columns: 20% 80%; gap: 16px; align-items: start; }

/* ============== LEFT INDEX ============== */
#apex-nav {
  border: 1px solid #e5e7eb; border-radius: 10px; background: #fff;
  height: calc(100vh - 100px); overflow-y: auto; margin-left: 0 !important; padding: 12px;
}
#apex-nav h3 { font-size: 1.05rem; margin: 4px 0 10px 0; color: #475569; }
#apex-nav a { display: block; padding: 6px 8px; margin-bottom: 6px; text-decoration: none;
  color: #0f172a; border-radius: 8px; border: 1px solid transparent; }
#apex-nav a:hover, #apex-nav a.active { background: #eef2ff; border-color: #c7d2fe; }

/* ============== RIGHT CONTENT ============== */
#apex-content {
  border: 1px solid #e5e7eb; border-radius: 10px; background: #fff;
  min-height: calc(100vh - 100px); overflow-y: auto; padding: 16px;
}
/* Tabs (only one visible) */
.tab { display: none; }
.tab.visible { display: block; }

/* Code blocks */
#apex-content pre { background: #0f172a; color: #e5e7eb; padding: 12px; border-radius: 8px; overflow-x: auto; }

@media (max-width: 900px) {
  #apex-grid { grid-template-columns: 1fr; }
  #apex-nav { height: auto; }
  #apex-content { min-height: 60vh; }
}
</style>

<div id="apex-wrap">

  <!-- TOP HEADER -->
  <h1 id="apex-title">KPIT APEX Lab: Linux Assignment Page</h1>

  <!-- 20% / 80% GRID -->
  <div id="apex-grid">

    <!-- LEFT: INDEX -->
    <aside id="apex-nav">
      <h3>Index</h3>
      #signalSignals</a>
      #threadThreads</a>
      <hr>
      <strong>POSIX IPC</strong>
      #pipePipes (Unnamed)</a>
      #fifoFIFOs (Named Pipes)</a>
      #mqueueMessage Queues</a>
      #shmShared Memory</a>
    </aside>

    <!-- RIGHT: CONTENT (pre-rendered HTML; no raw Markdown) -->
    <main id="apex-content">
      <article id="tab-signal" class="tab">{{ MD_SIGNAL | markdownify }}</article>
      <article id="tab-thread" class="tab">{{ MD_THREAD | markdownify }}</article>
      <article id="tab-pipe"   class="tab">{{ MD_PIPE   | markdownify }}</article>
      <article id="tab-fifo"   class="tab">{{ MD_FIFO   | markdownify }}</article>
      <article id="tab-mqueue" class="tab">{{ MD_MQUEUE | markdownify }}</article>
      <article id="tab-shm"    class="tab">{{ MD_SHM    | markdownify }}</article>
    </main>

  </div>
</div>

<script>
/* Minimal, local JS (no external libs) just to switch visible section and highlight the active index link */
(function () {
  const tabs = {
    signal:  document.getElementById('tab-signal'),
    thread:  document.getElementById('tab-thread'),
    pipe:    document.getElementById('tab-pipe'),
    fifo:    document.getElementById('tab-fifo'),
    mqueue:  document.getElementById('tab-mqueue'),
    shm:     document.getElementById('tab-shm')
  };
  const nav = document.getElementById('apex-nav');

  function show(which) {
    // default to 'signal' if unknown or missing
    if (!tabs[which]) which = 'signal';
    // hide all, show one
    Object.values(tabs).forEach(el => el.classList.remove('visible'));
    tabs[which].classList.add('visible');
    // highlight nav
    nav.querySelectorAll('a[data-tab]').forEach(a => a.classList.toggle('active', a.dataset.tab === which));
  }

  // handle clicks in the index
  nav.addEventListener('click', (e) => {
    const a = e.target.closest('a[data-tab]');
    if (!a) return;
    e.preventDefault();
    const which = a.dataset.tab;
    history.pushState({ which }, '', '#' + which);
    show(which);
  });

  // back/forward
  window.addEventListener('popstate', (e) => {
    const which = (e.state && e.state.which) || (location.hash ? location.hash.slice(1) : 'signal');
    show(which);
  });

  // initial selection
  const initial = location.hash ? location.hash.slice(1) : 'signal';
  show(initial);
})();
</script>
