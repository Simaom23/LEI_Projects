package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.io.*; 

/**
 *  Define as Publicações do tipo Capítulo de Livro.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class LivroCapitulo extends Livro implements Serializable{

    private String nomeCap;
    private int pagI;
    private int pagF;

    /**
     * Construtor da Classe LivroCapitulo.
     * @param nomeCap Nome do Capítulo.
     * @param pagI Página Inicial do Capítulo.
     * @param pagF Página Final do Capítulo.
     * @param editora Editora do Livro.
     * @param isbn ISBN do Livro.
     * @param autores Array de autores.
     * @param titulo Titulo do Artigo.
     * @param keywords Array de keywords.
     * @param anoPub Ano de publicação do artigo.
     * @param dimensao Dimensão do artigo.
     * @param resumo Resumo do artigo.
     */
    public LivroCapitulo(String nomeCap, int pagI, int pagF, String editora, String isbn, String[] autores, String titulo, String[] keywords, int anoPub, int dimensao, String resumo) {
        super(editora, isbn, autores, titulo, keywords, anoPub, dimensao, resumo);
        this.nomeCap = nomeCap;
        this.pagI = pagI;
        this.pagF = pagF;
    }

    /**
     *
     * @return Tipo de Publicação (5)
     */
    @Override
    public int tipoPub() {
        return 5;
    }

    /**
     * Calcula o impacto através da dimensão do capítulo do livro.
     * @return Impacto de Publicação ("A", "B" ou "C"). 
     */
    @Override
    public String fatorImpacto() {
        if (getDimensao() >= 7500) {
            return("A");
        } else if (getDimensao() < 7500 && getDimensao() >= 2500) {
            return("B");
        } else {
            return("C");
        }
    }

    /**
     *
     * @return String para impressão da informação do capítulo do livro.
     */
    @Override
    public String toString() {
        return "Artigo de Conferência -> Autores: " + getAutoresString() + ", Título: " + getTitulo() + ", Ano de Publicação: " + getAnoPub() 
                +", Impacto: " + getImpacto() + ", Nome do Capítulo: " + nomeCap + ", Página Inicial: " + pagI + ", Página Final:" + pagF;
    }
    
}
