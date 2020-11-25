typedef struct {
    Peta* AsalKuadranPeta;
    Peta* TargetKuadranPeta;
    char InputArah;
} Garis;

typedef struct {
    Garis Edge[8];
} GrafPeta;

GrafPeta GrafUntukPeta;
