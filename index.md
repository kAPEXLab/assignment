---
title: KPIT APEX Lab — Assignments
layout: default
---

<div class="apex-layout">
  <aside class="apex-sidebar">
    <h2>Assignments</h2>
    <nav>
      <a href="signal.md" target="apexFrame">Signals</a>
      <a href="thread.md" target="apexFrame">Threads</a>
      <hr>
      <strong>POSIX IPC</strong>
      <a href="posixpipe.md" target="apexFrame">Pipes (Unnamed)</a>
      <a href="posixfifo.md" target="apexFrame">FIFOs (Named Pipes)</a>
      <a href="posixmsgque.md" target="apexFrame">Message Queues</a>
      <a href="posixshm.md" target="apexFrame">Shared Memory</a>
    </nav>
  </aside>

  <main class="apex-content">
    <!-- Default page loaded on first visit -->
    <iframe name="apexFrame" id="apexFrame" src="signal.md" title="Assignment Viewer" loading="lazy"></iframe>
  </main>
</div>

<style>
  :root {
    --sidebar-width: 280px;
    --gap: 16px;
    --border: #e5e7eb;
    --bg: #ffffff;
  }
  .apex-layout {
    display: grid;
    grid-template-columns: var(--sidebar-width) 1fr;
    gap: var(--gap);
    align-items: start;
  }
  .apex-sidebar {
    position: sticky;
    top: 0;
    height: calc(100vh - 60px);
    overflow: auto;
    padding: 12px 12px 24px 12px;
    border: 1px solid var(--border);
    border-radius: 10px;
    background: var(--bg);
  }
  .apex-sidebar h2 {
    margin: 4px 0 10px;
    font-size: 1.05rem;
  }
  .apex-sidebar nav {
    display: grid;
    gap: 8px;
  }
  .apex-sidebar nav a {
    text-decoration: none;
    color: #0f172a;
    padding: 6px 8px;
    border-radius: 8px;
    border: 1px solid transparent;
  }
  .apex-sidebar nav a:hover {
    background: #f8fafc;
    border-color: var(--border);
  }
  .apex-content {
    min-height: calc(100vh - 60px);
  }
  #apexFrame {
    width: 100%;
    height: calc(100vh - 60px);
    border: 1px solid var(--border);
    border-radius: 10px;
    background: var(--bg);
  }

  /* Small screens: stack */
  @media (max-width: 960px) {
    .apex-layout {
      grid-template-columns: 1fr;
    }
    .apex-sidebar {
      position: relative;
      height: auto;
    }
    #apexFrame {
      height: 70vh;
    }
  }
</style>

<noscript>
  <p><strong>Note:</strong> This page uses an iframe for right‑side viewing.
  If you prefer navigation without iframe, ask for the “single‑page loader” version.</p>
</noscript>
