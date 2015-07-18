objects = observer decorator simple_factory factory_method abstract_factory singleton command adapter facade template_method iterator

# g++ -g $().cpp -o $()


all: $(objects)

$(objects): %: %.cpp
	g++ -g $< -o $@

.PHONY: clean
clean:
	@-rm -f $(objects)
