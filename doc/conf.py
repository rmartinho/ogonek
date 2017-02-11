#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
import sphinx_rtd_theme


# -- General configuration ------------------------------------------------

primary_domain = 'cpp'
extensions = ['sphinx.ext.todo']
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
project = 'Ogonek'
copyright = '2017, R. Martinho Fernandes'
author = 'R. Martinho Fernandes'
version = '0.6'
release = '0.6.0'
language = None
exclude_patterns = []
pygments_style = 'sphinx'
todo_include_todos = True

rst_prolog = """
.. include:: /include.txt
"""

# -- Options for HTML output ----------------------------------------------

html_theme = 'sphinx_rtd_theme'
html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]
# html_theme_options = {}
# html_static_path = ['_static']


# -- Options for HTMLHelp output ------------------------------------------

# Output file base name for HTML help builder.
htmlhelp_basename = 'Ogonekdoc'


# -- Options for LaTeX output ---------------------------------------------

latex_engine = 'xelatex'
latex_elements = {
    'fontenc': '\\usepackage{fontspec}',
    'fontpkg': '''\
\\setmainfont{Noto Serif}
\\setsansfont{Noto Sans}
\\setmonofont{Noto Mono}''',
    'geometry': '\\usepackage[vmargin=2.5cm, hmargin=3cm]{geometry}',
    'preamble': '''\
\\usepackage[titles]{tocloft}
\\cftsetpnumwidth {1.25cm}\\cftsetrmarg{1.5cm}
\\setlength{\\cftchapnumwidth}{0.75cm}
\\setlength{\\cftsecindent}{\\cftchapnumwidth}
\\setlength{\\cftsecnumwidth}{1.25cm}''',
    'fncychap': '\\usepackage[Bjornstrup]{fncychap}',
    'printindex': '\\footnotesize\\raggedright\\printindex',
}
latex_show_urls = 'footnote'

latex_documents = [
    (master_doc, 'Ogonek.tex', 'Ogonek Documentation',
     'R. Martinho Fernandes', 'manual'),
]


# -- Options for manual page output ---------------------------------------

man_pages = [
    (master_doc, 'ogonek', 'Ogonek Documentation',
     [author], 1)
]


# -- Options for Texinfo output -------------------------------------------

texinfo_documents = [
    (master_doc, 'Ogonek', 'Ogonek Documentation',
     author, 'Ogonek', 'A C++ Unicode library.',
     'Miscellaneous'),
]



# -- Options for Epub output ----------------------------------------------

# Bibliographic Dublin Core info.
epub_title = project
epub_author = author
epub_publisher = author
epub_copyright = copyright

# epub_identifier = ''

# epub_uid = ''

epub_exclude_files = ['search.html']
