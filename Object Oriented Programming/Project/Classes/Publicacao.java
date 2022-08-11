package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.io.*;
import java.util.Comparator;

/**
 * Define as Publicações do CISUC.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class Publicacao implements Serializable {

    private String[] autores;
    private String titulo;
    private String[] keywords;
    private int anoPub;
    private int dimensao;
    private String resumo;
    private String impacto;
    private int tipo;

    /**
     * Construtor da classe Publicacao.
     * @param autores Array de autores da Publicação.
     * @param titulo Titulo da Publicação.
     * @param keywords Array de keywords da Publicação.
     * @param anoPub Ano de Publicação.
     * @param dimensao Dimensão da Publicação.
     * @param resumo Resumo da Publicação.
     */
    public Publicacao(String[] autores, String titulo, String[] keywords, int anoPub, int dimensao, String resumo) {
        this.autores = autores;
        this.titulo = titulo;
        this.keywords = keywords;
        this.anoPub = anoPub;
        this.dimensao = dimensao;
        this.resumo = resumo;
        this.impacto = fatorImpacto();
        this.tipo = tipoPub();
    }

    /**
     *
     * @return Dimensão da Publicação.
     */
    public int getDimensao() {
        return dimensao;
    }

    /**
     *
     * @return Tipo da Publicação.
     */
    public int getTipo() {
        return tipo;
    }

    /**
     *
     * @return Ano da Publicação.
     */
    public int getAnoPub() {
        return anoPub;
    }

    /**
     *
     * @return Array de autores da Publicação.
     */
    public String[] getAutores() {
        return autores;
    }

    /**
     * 
     * @return Tipo de Publicação (Default - 0, 1 - ArtConferencia, 2 - ArtRevista, 3 - Livro, 4 - LivroCOnf, 5 - CapLivro).
     */
    public int tipoPub() {
        return 0;
    }

    /**
     *
     * @return Fator de Impacto de Publicação ("A", "B" ou "C").
     */
    public String getFatorImpacto() {
        return impacto;
    }

    /**
     * 
     * @return Fator de Impacto "NULL" caso a Publicação nao seja especificada.
     */
    public String fatorImpacto() {
        return ("NULL");
    }

    /**
     *
     * @return Titulo da Publicação.
     */
    public String getTitulo() {
        return titulo;
    }

    /**
     *
     * @return Resumo da Publicação
     */
    public String getResumo() {
        return resumo;
    }

    /**
     *
     * @return Impacto da Publicação
     */
    public String getImpacto() {
        return impacto;
    }
    
    /**
     *
     * @return String de autores legível para o utilizador.
     */
    public String getAutoresString(){
        String temp = "(";
        int cont = 0;
        for (String autor : getAutores()) {
            if (cont < getAutores().length - 1) {
                temp += autor + ", ";
            }
            else{
                temp += autor + ")";
            }
            cont++;
        }
        return temp;
    }

    /**
     * Comparator para ordenar as Publicações pelo seu ano.
     */
    public static Comparator<Publicacao> anoOrganiza = new Comparator<Publicacao>() {
        @Override
        public int compare(Publicacao p1, Publicacao p2) {
            return (int) (p1.getAnoPub() - p2.getAnoPub());
        }
    };

    /**
     * Comparator para ordenar as Publicações pelo seu impacto. 
     */
    public static Comparator<Publicacao> impactoOrganiza = new Comparator<Publicacao>() {
        @Override
        public int compare(Publicacao p1, Publicacao p2) {
            return p1.getFatorImpacto().compareTo(p2.getFatorImpacto());
        }
    };

    /**
     * Comparator para ordenar as Publicações pelo seu tipo.
     */
    public static Comparator<Publicacao> tipoOrganiza = new Comparator<Publicacao>() {
        @Override
        public int compare(Publicacao p1, Publicacao p2) {
            return (int) (p1.getTipo() - p2.getTipo());
        }
    };

    /**
     *
     * @return String para impressão das informações da Publicação.
     */
    @Override
    public String toString() {
        return "Autores: " + autores + ", Título: " + titulo + ", Keywords: " + keywords + ", Ano de Pub: " + anoPub + ", Dimensão: " + dimensao + ", Resumo: " + resumo + ", Impacto: " + impacto;
    }

}
