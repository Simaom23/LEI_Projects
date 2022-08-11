package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.io.*; 

/**
 * Define as Publicações do tipo Artigo de Revista.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class ArtRevista extends Publicacao implements Serializable{

    private String nome;
    private String data;
    private String numero;

    /**
     * Construtor da classe ArtRevista.
     * @param nome Nome da Revista.
     * @param data Data da Revista.
     * @param numero Número da Revista.
     * @param autores Array de autores.
     * @param titulo Titulo do Artigo.
     * @param keywords Array de keywords.
     * @param anoPub Ano de publicação do artigo.
     * @param dimensao Dimensão do artigo.
     * @param resumo Resumo do artigo.
     */
    public ArtRevista(String nome, String data, String numero, String[] autores, String titulo, String[] keywords, int anoPub, int dimensao, String resumo) {
        super(autores, titulo, keywords, anoPub, dimensao, resumo);
        this.nome = nome;
        this.data = data;
        this.numero = numero;
    }

    /**
     *
     * @return Tipo de Publicação (2)
     */
    @Override
    public int tipoPub(){
        return 2;
    }
    
    /**
     * Calcula o impacto através da dimensão do artigo de revista.
     * @return Impacto de Publicação ("A", "B" ou "C"). 
     */
    @Override
    public String fatorImpacto() {
        if (getDimensao() >= 1000) {
            return("A");
        } else if (getDimensao() < 1000 && getDimensao() >= 500) {
            return("B");
        } else {
            return("C");
        }
    }

    /**
     *
     * @return String para impressão da informação do artigo de revista.
     */
    @Override
    public String toString() {
        return "Artigo de Revista -> Autores: " + getAutoresString() + ", Título: " + getTitulo() + ", Ano de Publicação: " + getAnoPub()
                +", Impacto: " + getImpacto() + ", Nome: " + nome + ", Data: " + data + ", Número: " + numero;
    }
    
}
