all: sensors.pdf show

.PHONY:clean
clean:
	rm -f *.aux *.toc *.log *.pdf *.out

sensors.pdf: sensors.tex
	pdflatex sensors.tex
	pdflatex sensors.tex

show: sensors.pdf
	evince sensors.pdf
