
josephus: josephus.hs 
	stack ghc --  --make -O3 ./josephus.hs

.PHONY: clean solve

solve: josephus
	./josephus 3012210


clean:
	-rm *.hi *.o *.hspp josephus *.so josephus

