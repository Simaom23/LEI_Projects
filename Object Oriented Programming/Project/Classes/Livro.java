package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.io.*; 

/**
 * Define as Publicações do tipo Livro.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class Livro extends Publicacao implements Serializable{

    private String editora;
    private String isbn;

    /**
     * Contrutor da classe Livro.
     * @param editora Editora do Livro.
     * @param isbn ISBN do Livro.
     * @param autores Array de autores.
     * @param titulo Titulo do Artigo.
     * @param keywords Array de keywords.
     * @param anoPub Ano de publicação do artigo.
     * @param dimensao Dimensão do artigo.
     * @param resumo Resumo do artigo.
     */
    public Livro(String editora, String isbn, String[] autores, String titulo, String[] keywords, int anoPub, int dimensao, String resumo) {
        super(autores, titulo, keywords, anoPub, dimensao, resumo);
        this.editora = editora;
        this.isbn = isbn;
    }

    /**
     *
     * @return Tipo de Publicação (3)
     */
    @Override
    public int tipoPub(){
        return 3;
    }
    
    /**
     * Calcula o impacto através da dimensão do livro.
     * @return Impacto de Publicação ("A", "B" ou "C"). 
     */
    @Override
    public String fatorImpacto() {
        if (getDimensao() >= 10000) {
            return("A");
        } else if (getDimensao() < 10000 && getDimensao() >= 5000) {
            return("B");
        } else {
            return("C");
        }
    }

    /**
     *
     * @return String para impressao da informação do livro.
     */
    @Override
    public String toString() {
        return "Livro -> Autores: " + getAutoresString() + ", Título: " + getTitulo() + ", Ano de Publicação: " + getAnoPub()
                +", Impacto: " + getImpacto() + ", Editora:" + editora + ", ISBN:" + isbn;
    }
    
}
