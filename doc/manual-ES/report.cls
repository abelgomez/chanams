%%%
%%% 2020/06/12 -- v0.1 
%%% A. Gomez
%%%
%%% Modified report class based on the report template provided by Karol Kozio 
%%% (www.karol-koziol.net) under Gnu Public Licence (GPL) terms
%%%
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{report}[
  2020/06/12 -- v0.1 -- 
  A. Gomez's modified report class based on the report template provided by 
  Karol Kozio (www.karol-koziol.net) under Gnu Public Licence (GPL) terms
]

%%%
%%% Engine detector
%%% 

\RequirePackage{ifxetex,ifluatex} 
\newif\ifxetexorluatex
\ifxetex
  \xetexorluatextrue
\else
  \ifluatex
    \xetexorluatextrue
  \else
    \xetexorluatexfalse
  \fi
\fi


%%%
%%% Base class
%%%

\LoadClassWithOptions{article}

\makeatletter
\newif\if@partial\@partialfalse
\DeclareOption{partial}{\@partialtrue}
\newcommand\iffull[1]{\if@partial\else\trim@spaces{#1}\fi}
\newcommand\ifpartial[1]{\if@partial\trim@spaces{#1}\fi}
\makeatother

\ProcessOptions\relax

%%%
%%% Variables
%%%

\RequirePackage{trimspaces}
\makeatletter
\newcommand{\subtitlea}[1]{\gdef\@subtitlea{\trim@spaces{#1}}}
\newcommand{\subtitleb}[1]{\gdef\@subtitleb{\trim@spaces{#1}}}
\newcommand{\copyrightnotice}[1]{\gdef\@copyrightnotice{\trim@spaces{#1}}}
\newcommand{\cover}[1]{\gdef\@cover{\trim@spaces{#1}}}
\newcommand{\back}[1]{\gdef\@back{\trim@spaces{#1}}}


\date{\today}
\cover{images/template/cover}
\back{images/template/back}
\makeatother

%%%
%%% Colors
%%%

\RequirePackage[dvipsnames]{xcolor}
\definecolor{main}{HTML}{bf1300}
\definecolor{comp1}{HTML}{85b4ff}
\definecolor{comp2}{HTML}{edc9c7}
\definecolor{gray}{HTML}{333333}

%%%
%%% Fonts
%%%

\ifxetexorluatex 
  \RequirePackage[no-math]{fontspec}
  \RequirePackage{anyfontsize}
  \defaultfontfeatures{Mapping=tex-text,LetterSpace=-1pt}
  \setmainfont[
    Path=fonts/,
    BoldFont=Roboto-Regular.ttf,
    ItalicFont=Roboto-LightItalic.ttf,
    BoldItalicFont=Roboto-Italic.ttf,
    Scale=0.9,
  ]
  {Roboto-Light.ttf}
  \newfontfamily\headingfont[
    Path=fonts/,
    BoldFont=Roboto-Bold.ttf,
    ItalicFont=Roboto-Italic.ttf,
    BoldItalicFont=Roboto-BoldItalic.ttf,
    Scale=0.9,
  ]
  {Roboto-Regular.ttf}
  
  \newcommand{\textcaption}[1]{\uppercase{#1}}
  \newcommand*\quotefont{\fontspec[Path=fonts/]{Roboto-Bold.ttf}}
\else
  % Use embedded Helvetica Regular if using LaTeX
  % Warning: Layout may not be accurate
  \typeout{**WARNING**: Using Helvetica as a font replacement for the document body}
  \RequirePackage{helvet}
  \renewcommand*\familydefault{\sfdefault}
  \newcommand*{\headingfont}{\sffamily\bfseries}
  \newcommand{\textcaption}[1]{\uppercase{#1}}
  \newcommand*\quotefont{}
\fi

%%%
%%% Formatting
%%%

% Description labels
\renewcommand{\descriptionlabel}[1]{\hspace{\labelsep}\textcolor{main}{\uppercase{#1}}}
\DeclareTextFontCommand{\emph}{\color{main}\em}

%%%
%%% Hyperlinks
%%%
\RequirePackage{hyperref}
\hypersetup{
    colorlinks=true,
    linkcolor={.!80},
    citecolor={.!80!main},
    urlcolor={.!80!main}
}

%%%
%%% Page configuration
%%%

\RequirePackage{geometry}
\geometry{
  a5paper,
  headheight=15pt,
  top=2.5cm, bottom=3cm, left=1.5cm, right=1.5cm,
  foot=1cm
}
\setlength{\textfloatsep}{2em}
\setlength{\intextsep}{2em}
\setlength{\columnsep}{1.5em}
%\setlength{\parindent}{2.5em}
%\setlength{\parskip}{1em}

\linespread{1.08}
\RequirePackage[bottom,hang,flushmargin]{footmisc}

%%%
%%% Captions
%%%

\RequirePackage{indentfirst}
\RequirePackage[hang]{caption}
\DeclareCaptionFormat{upper}{#1#2{\textcaption{#3}}\par}
\captionsetup{labelfont={bf,color=gray},textfont={normalsize,color=gray},format = upper,figurename=FIGURA,tablename=TABLA}

%%%
%%% Sections
%%%

\RequirePackage[noindentafter]{titlesec}
\makeatletter
\newcommand{\sectionbreak}{\cleardoublepage}
\setcounter{secnumdepth}{4}
\titleformat{\section}{\color{main}\headingfont\Large\bfseries\uppercase}{\thesection}{1em}{}[\titlerule]
\titleformat{\subsection}{\color{main}\headingfont\large\bfseries\uppercase}{\thesubsection}{1em}{}
\titleformat{\subsubsection}{\color{main}\headingfont\bfseries\uppercase}{\thesubsubsection}{1em}{}
\titleformat{\paragraph}{\color{main}\headingfont\bfseries\uppercase}{\theparagraph}{1em}{}
\titleformat{\subparagraph}[runin]{\color{main}\uppercase}{\thesubparagraph}{0pt}{}
\titlespacing{\subparagraph}{0pt}{1em}{1em}
\let\@refname\refname
\renewcommand{\refname}{\expandafter\MakeUppercase\expandafter{\@refname}}
\makeatother
\renewcommand{\contentsname}{\uppercase{ÍNDICE}}

%%%
%%% Environments
%%%

\newenvironment{itemizecompact}
{\setlist[itemize]{itemsep=0mm}\begin{itemize}}
{\end{itemize}}
\newenvironment{enumeratecompact}
{\setlist[enumerate]{itemsep=0mm}\begin{enumerate}}
{\end{enumerate}}
\newenvironment{descriptioncompact}
{\setlist[description]{itemsep=0mm}\begin{description}}
{\end{description}}


\RequirePackage{etoolbox}
\RequirePackage{tikz}

\newcommand*\quotesize{80}
% Make commands for the quotes
\newcommand*{\openquote}
   {\tikz[remember picture,overlay,xshift=-5ex,yshift=-4ex]
   \node (OQ) {\quotefont\fontsize{\quotesize}{\quotesize}\selectfont\color{main}``};\kern0pt}

\newcommand*{\closequote}[1]
  {\tikz[remember picture,overlay,xshift=5ex,yshift={#1}]
   \node (CQ) {\quotefont\fontsize{\quotesize}{\quotesize}\selectfont\color{main}''};}

\newcommand*\shadedauthorformat{\emph} % define format for the author argument

% Now a command to allow left, right and centre alignment of the author
\newcommand*\authoralign[1]{%
  \if#1l
    \def\authorfill{}\def\quotefill{\hfill}
  \else
    \if#1r
      \def\authorfill{\hfill}\def\quotefill{}
    \else
      \if#1c
        \gdef\authorfill{\hfill}\def\quotefill{\hfill}
      \else\typeout{Invalid option}
      \fi
    \fi
  \fi}
% wrap everything in its own environment which takes one argument (author) and one optional argument
% specifying the alignment [l, r or c]
%
\RequirePackage{scrextend}
\newenvironment{fancyquote}[2][l]%
{\begin{addmargin}[4ex]{4ex}\authoralign{#1}
\ifblank{#2}
   {\def\shadequoteauthor{}\def\yshift{-0.2ex}\def\quotefill{\hfill}}
   {\def\shadequoteauthor{\par\authorfill\shadedauthorformat{#2}}\def\yshift{2ex}}
\begin{quote}\openquote}
{\shadequoteauthor\quotefill\closequote{\yshift}\end{quote}\vspace{\parsep}\end{addmargin}}




%%%
%%% Headers and footers
%%%

\RequirePackage{fancyhdr}
\RequirePackage{calc}
\pagestyle{fancy}
\makeatletter
\newlength{\myheight}
\renewcommand{\sectionmark}[1]{\markright{\arabic{section}\hspace{1em}\uppercase{#1}}}
\lhead{}
\chead{}
\cfoot{}
\fancyhead[EL]{\color{main}\rightmark}
\fancyhead[ER]{}
\fancyhead[OL]{}
\fancyhead[OR]{\color{main}\rightmark}
\fancyfoot[EL]{\color{main}\thepage}
\fancyfoot[ER]{\color{main}\@title}
\fancyfoot[OR]{\color{main}\thepage}
\fancyfoot[OL]{\color{main}\@subtitlea~--~\@subtitleb}
\renewcommand\headrulewidth{0pt}
\renewcommand\footrulewidth{0pt}
\makeatother

%%%
%%% Titlepage
%%%

\newcommand*\cleartoleftpage{%
  \clearpage
  \ifodd\value{page}\hbox{}\newpage\fi
}

% Picture on cover page
\RequirePackage{eso-pic}
\makeatletter
\newcommand\BackgroundPic{%
\put(0,0){%
\parbox[b][\paperheight]{\paperwidth}{%
\vfill
\centering
\includegraphics[width=\paperwidth,height=\paperheight,%
keepaspectratio]{\@cover}%
\vfill
}}}
\newcommand\BackgroundBackPic{%
\put(0,0){%
\parbox[b][\paperheight]{\paperwidth}{%
\vfill
\centering
\includegraphics[width=\paperwidth,height=\paperheight,%
keepaspectratio]{\@back}%
\vfill
}}}
\makeatother

% Authors
\makeatletter
\renewcommand{\maketitle}{
\newgeometry{left=16mm, textwidth=116mm, top=20mm, bottom=15mm}
\thispagestyle{empty}
\AddToShipoutPicture*{\BackgroundPic}
\ClearShipoutPicture
\begin{flushleft}
  \parbox{70mm}{\raggedright\fontsize{32pt}{32}\bfseries\headingfont\noindent\trim@spaces{\@title}}
  \vfill
  \def\and{\end{tabular}~{\fontsize{25}{0}\selectfont\rmfamily\raisebox{-3.5pt}{/}}~\begin{tabular}[t]{l}} 
  {
    %\bfseries\headingfont\fontsize{18pt}{0}\selectfont
    %\begin{tabular}[t]{l}
    %  \@author
    %\end{tabular}\par
  }
  \vspace{1em}
  {
    \global\let\and\relax
    \bfseries\headingfont\fontsize{18pt}{0}\selectfont
    \begin{tabular}{p{\textwidth}}
      \raggedleft\@subtitlea\\
      \smaller[2]{\textnormal{\@subtitleb}}
    \end{tabular}
  }
  \vspace{1em}
\end{flushleft}
\restoregeometry
\newpage
\thispagestyle{empty}
\phantom{~}
\vfill
{\urlstyle{rm}\small\noindent\trim@spaces{\@title},~\@subtitlea,~\@subtitleb~\textcopyright~\ifx\@copyrightnotice\empty\else\@copyrightnotice,\fi~\@date. All rights are reserved.}
\newpage
\thispagestyle{empty}
\ifpartial{
  \vspace*{\fill}
  \begin{center}
    \setlength{\fboxsep}{2em}
    \fcolorbox{main}{main}{
      \parbox{8cm}{
      \centering\fontsize{14pt}{17pt}\selectfont\color{white}
      Partial document building is ON:\\
      \vspace{2em}
      This document is a draft and may be incomplete}
    }
  \end{center}
  \vspace*{\fill}
  }
  \cleardoublepage
  \setcounter{page}{1}
}
\makeatother

\newcommand{\makeback}{
\clearpage
\pagestyle{empty}
\cleartoleftpage
\AddToShipoutPicture*{\BackgroundBackPic}
\ClearShipoutPicture{~}
\clearpage
}
\makeatother

%%%
%%% Clarifications
%%%

% Print them only if the notes package is loaded (c@pagenode exists)
% and there are notes defined within the document (pnotesavechap > 0)
\newcommand{\clarifications}{
\makeatletter
\ifcsname c@pagenote\endcsname
\ifthenelse{\value{pnotesavechap}>0}{\cleardoublepage\printnotes}{}
\fi
\makeatother
}

%%%
%%% Text boxes
%%%

% Fullbox
\RequirePackage[many]{tcolorbox}
\RequirePackage{wrapfig}
\def\fullboxbegin{
  \bigskip
  \begin{tcolorbox}[colback=main,colframe=main,coltext=white,arc=0mm,boxrule=0pt]
}
\def\fullboxend{
  \end{tcolorbox}\medskip
}

% Sidebox
%
% Floating sideboxes must receive a position (l-left, r-right, i-inner, o-outer)
% It is possible to define sideboxes with a single command that calculates the
% exact height needed for the box in lines. However this solution is overcomplex,
% and we do not use it conciously to avoid future problems
\makeatletter
\def\sideboxbegin{
  \@ifnextchar[{\@t@sideboxbegin}{\@e@sideboxbegin}
}
\def\@t@sideboxbegin[#1]#2{
  \begin{wrapfigure}[#1]{#2}{0.5\textwidth}
  \vspace{-\intextsep}
  \begin{tcolorbox}[colback=main,colframe=main,coltext=white,arc=0mm,boxrule=0pt,before upper={\parindent15pt}]
  \noindent\ignorespaces
} 
\def\@e@sideboxbegin#1{
  \begin{wrapfigure}{#1}{0.5\textwidth}
  \vspace{-\intextsep}
  \begin{tcolorbox}[colback=main,colframe=main,coltext=white,arc=0mm,boxrule=0pt,before upper={\parindent15pt}]
  \noindent\ignorespaces
}
\def\sideboxend{
  \end{tcolorbox}
  \vspace{-\intextsep}
  \end{wrapfigure}
}
\makeatother

% Framebox
\newcounter{frames}
\def\frameboxbegin#1{
  \bigskip
  \refstepcounter{frames}
  \begin{tcolorbox}[breakable,enhanced jigsaw,colback=white,colframe=main,arc=0mm,title={\MakeUppercase{\textbf{Frame \arabic{frames}}: #1}}]
}
\def\frameboxend{
  \end{tcolorbox}
}

% Important
\newcounter{important}
\def\importantbegin#1{
  \bigskip
  \refstepcounter{important}
  \begin{tcolorbox}[breakable,enhanced jigsaw,colback=white,colframe=main,arc=0mm,title={\MakeUppercase{\textbf{Importate}: #1}}]%\arabic{important}}: #1}}]
}
\def\importantend{
  \end{tcolorbox}
}

% Examples
\newcounter{tips}
\def\tipbegin#1{
  \bigskip
  \refstepcounter{tips}
  \begin{tcolorbox}[breakable,enhanced jigsaw,colback=white,colframe=comp1,arc=0mm,coltitle=black,title={\MakeUppercase{\textbf{Consejo}: #1}}]% \arabic{tips}}: #1}}]
}
\def\tipend{
  \end{tcolorbox}
}

% Notes
\newcounter{att}
\def\attbegin#1{
  \bigskip
  \refstepcounter{att}
  \begin{tcolorbox}[breakable,enhanced jigsaw,colback=white,colframe=comp2,arc=0mm,coltitle=black,title={\MakeUppercase{\textbf{Atención}: #1}}]% \arabic{att}}: #1}}]
}
\def\attend{
  \end{tcolorbox}
}
