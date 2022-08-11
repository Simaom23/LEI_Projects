package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.io.*; 

/**
 * Define as Publicações do tipo Livro de Conferência.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class LivroConferencia extends Livro implements Serializable{

    private String nomeConf;
    private int nArtigos;

    /**
     * Contrutor da classe LivroConferencia.
     * @param nomeConf Nome da conferencia.
     * @param nArtigos Nº Artigos.
     * @param editora Editora do Livro.
     * @param isbn ISBN do Livro.
     * @param autores Array de autores.
     * @param titulo Titulo do Artigo.
     * @param keywords Array de keywords.
     * @param anoPub Ano de publicação do artigo.
     * @param dimensao Dimensão do artigo.
     * @param resumo Resumo do artigo.
     */
    public LivroConferencia(String nomeConf, int nArtigos, String editora, String isbn, String[] autores, String titulo, String[] keywords, int anoPub, int dimensao, String resumo) {
        super(editora, isbn, autores, titulo, keywords, anoPub, dimensao, resumo);
        this.nomeConf = nomeConf;
        this.nArtigos = nArtigos;
    }
    
    /**
     *
     * @return Tipo de Publicação (4)
     */
    @Override
    public int tipoPub(){
        return 4;
    }
    
    /**
     * Calcula o impacto através da dimensão do livro de conferência.
     * @return Impacto de Publicação ("A", "B" ou "C"). 
     */
    @Override
    public String fatorImpacto() {
        if (getDimensao() >= 10000) {
            return("A");
        } else if (getDimensao() < 10000 && getDimensao() >= 500) {
            return("B");
        } else {
            return("C");
        }
    }

    /**
     *
     * @return String de impressão da informação do livro de conferência.
     */
    @Override
    public String toString() {
        return "Livro de Conferência -> Autores: " + getAutoresString() + ", Título: " + getTitulo() + ", Ano de Publicação: " + getAnoPub() 
                +", Impacto: " + getImpacto() + ", Nome da Conferência: " + nomeConf + ", Nº Artigos:" + nArtigos;
    }
    
}
