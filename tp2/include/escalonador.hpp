enum TipoEvento {
    CHEGADA = 0,
    TRANSPORTE = 1
};

struct Evento {
    double hora;        // Momento em que ocorre o evento
    TipoEvento tipo;    // Tipo: CHEGADA ou TRANSPORTE
    int de;             // Armazém de origem (somente TRANSPORTE)
    int para;           // Armazém de destino (somente TRANSPORTE)
    int pacote_id;      // Identificador único do pacote
};

class MinHeapEvento {
    public:
        MinHeapEvento(int capInicial = 16);
        ~MinHeapEvento();

        void insere(const Evento &ev);
        Evento retiraProximo();

        bool vazio() const;
        
    private:
        Evento *heap;      // array de eventos
        int tamanho;       // número atual de eventos no heap
        int capacidade;    // tamanho do array alocado

        bool ehAnterior(const Evento &a, const Evento &b);

        void siftUp(int idx);
        void siftDown(int idx);

        void redimensiona(int novaCap);
        void swap(Evento &a, Evento &b);
};

