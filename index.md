---
title: KPIT APEX Lab — Assignments
layout: default
---

<!--
Landing page with 20/80 split.
- Left: index (sticky)
- Right: content rendered from root-level .md files (no raw view)
- Hides logo, "View the Project on GitHub", and footer text for this page.
- Keeps ALL files at repo root.
-->

<style>
  /* Hide theme chrome ONLY on this landing page */
  /* jekyll-theme-minimal common selectors */
  .site-header,
  .site-footer,
  .page-header .project-name,
  .page-header .project-tagline,
  .footer-col-1, .footer-col-2, .footer-col-3,
  .wrapper .header,
  header .btn, /* "View the Project on GitHub" */
  a[href*="github.com"][class*="btn"] {
    display: none !important;
  }

  /* Page layout */
  :root {
    --sidebar-width: 20%;
    --content-width: 80%;
    --gap: 16px;
    --border: #e5e7eb;
    --bg: #ffffff;
    --link: #0f172a;
    --link-hover: #111827;
  }
  .apex-layout {
    display: grid;
    grid-template-columns: var(--sidebar-width) var(--content-width);
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
    color: var(--link);
    padding: 6px 8px;
    border-radius: 8px;
    border: 1px solid transparent;
    display: block;
