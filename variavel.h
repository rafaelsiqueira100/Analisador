#ifndef VARIAVEL_H
#define VARIAVEL_H
#include "simbolo.h"
#include "tiposimbolo.h"


class variavel: public Simbolo
{
    public:
        variavel(string, int, TipoSimbolo);
        virtual ~variavel();

    protected:

    private:
};

#endif // VARIAVEL_H
