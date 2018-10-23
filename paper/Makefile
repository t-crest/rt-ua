all:

check:
	-../../misc/bin/duplicates *.tex
	-../../misc/bin/weasel *.tex
	-../../misc/bin/passive *.tex

msbib:
	cat ../../../bib/*.bib > msbib-url.bib
	sed s/\ \ url/\ \ no-url/ < msbib-url.bib > msbib.bib
	rm msbib-url.bib

clean:
	rm -f *.aux *.bbl *.blg *.log *.out *.pdf *.gz
