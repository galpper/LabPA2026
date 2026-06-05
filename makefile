executable = Main
compiler = g++
compiler-options = -g -Wall -Wextra -Werror

ifdef OS
	executable := $(executable).exe
endif

build:
	$(compiler) $(compiler-options) -o $(executable) ICollection/Integer.cpp ICollection/String.cpp ICollection/collections/List.cpp ICollection/collections/ListIterator.cpp ICollection/collections/ListNode.cpp ICollection/collections/OrderedDictionary.cpp ICollection/collections/OrderedDictionaryEntry.cpp ICollection/interfaces/ICollectible.cpp ICollection/interfaces/ICollection.cpp ICollection/interfaces/IDictionary.cpp ICollection/interfaces/IIterator.cpp ICollection/interfaces/IKey.cpp ICollection/interfaces/OrderedKey.cpp Clases/cpp/administracionpropiedad.cpp Clases/cpp/agenda.cpp Clases/cpp/apartamento.cpp Clases/cpp/casa.cpp Clases/cpp/cliente.cpp Clases/cpp/direccion.cpp Clases/cpp/inmobiliaria.cpp Clases/cpp/inmueble.cpp Clases/cpp/propietario.cpp Clases/cpp/publicacion.cpp Clases/cpp/usuario.cpp DataType/cpp/dtadministra.cpp DataType/cpp/dtcliente.cpp DataType/cpp/dtcuentabancaria.cpp DataType/cpp/dtdireccion.cpp DataType/cpp/DTFecha.cpp DataType/cpp/dtinmobiliaria.cpp DataType/cpp/dtinmueble.cpp DataType/cpp/dtinmueblepropietario.cpp DataType/cpp/dtpropietario.cpp DataType/cpp/dtpublicacion.cpp ISistema.cpp Factory.cpp Sistema.cpp main.cpp

.PHONY: clean
clean:
	rm -f $(executable)
