objects = observer decorator simple_factory factory_method abstract_factory singleton command adapter facade
objects += template_method iterator composite state
# g++ -g $().cpp -o $()


all: $(objects)

$(objects): %: %.cpp
	g++ -g $< -o $@

.PHONY: clean
clean:
	@-rm -f $(objects)
