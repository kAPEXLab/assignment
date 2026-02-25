<!-- DEBUG START -->
{% for p in site.pages %}
- TITLE: {{ p.title | inspect }} |
  NAV: {{ p.nav | inspect }} |
  CATEGORY: {{ p.category | inspect }} |
  URL: {{ p.url | inspect }}
{% endfor %}
<!-- DEBUG END -->

---
layout: default
title: Home
nav: true
nav_order: 1
---

Select the desired topic from the index to view its contents.
