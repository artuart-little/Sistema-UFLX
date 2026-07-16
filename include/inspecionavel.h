#ifndef INSPECIONAVEL_H
#define INSPECIONAVEL_H

class Inspecionavel {
public:
    virtual void realizar_inspecao() const = 0;
    virtual ~Inspecionavel() = default;
};

#endif // INSPECIONAVEL_H