package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.io.*; 

/**
 * Define as Publicações do tipo Artigo de Conferência.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class ArtConferencia extends Publicacao implements Serializable{

    private String nomeConf;
    private String data;
    private String localizacao;

    /**
     * Construtor da classe ArtConferencia.
     * @param nomeConf Nome da Conferência.
     * @param data Data da Confência.
     * @param localizacao Localização da Conferência.
     * @param autores Array de autores.
     * @param titulo Titulo do Artigo.
     * @param keywords Array de keywords.
     * @param anoPub Ano de publicação do artigo.
     * @param dimensao Dimensão do artigo.
     * @param resumo Resumo do artigo.
     */
    public ArtConferencia(String nomeConf, String data, String localizacao, String[] autores, String titulo, String[] keywords, int anoPub, int dimensao, String resumo) {
        super(autores, titulo, keywords, anoPub, dimensao, resumo);
        this.nomeConf = nomeConf;
        this.data = data;
        this.localizacao = localizacao;
    }

    /**
     *
     * @return Tipo de Publicação (1)
     */
    @Override
    public int tipoPub() {
        return 1;
    }

    /**
     * Calcula o impacto através da dimensão do artigo de conferência.
     * @return Impacto de Publicação ("A", "B" ou "C"). 
     */
    @Override
    public String fatorImpacto() {
        if (getDimensao() >= 500) {
            return("A");
        } else if (getDimensao() < 500 && getDimensao() >= 200) {
            return("B");
        } else {
            return("C");
        }
    }

    /**
     *
     * @return String para impressão das informações do artigos de conferência.
     */
    @Override
    public String toString() {
        return "Artigo de Conferência -> Autores: " + getAutoresString() + ", Título: " + getTitulo() + ", Ano de Publicação: " + getAnoPub() 
                +", Impacto: " + getImpacto() + ", Nome da Conferência:" + nomeConf + ", Data: " + data + ", Localização: " + localizacao;
    }
    
}
