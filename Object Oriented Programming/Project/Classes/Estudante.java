package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.io.*;

/**
 * Define os Investigadores do tipo Estudante.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class Estudante extends Investigador implements Serializable {

    private String tTese;
    private String cDate;
    private String orientador;

    /**
     * Construtor da classe Estudante.
     * @param tTese Título da tese do Estudante.
     * @param cDate Data de conclusão de tese do Estudante.
     * @param orientador Nome do orientador do Estudante.
     * @param nome Nome do Estudante.
     * @param email Email do Estudante.
     * @param grupo Grupo do Estudante
     */
    public Estudante(String tTese, String cDate, String orientador, String nome, String email, String grupo) {
        super(nome, email, grupo);
        this.tTese = tTese;
        this.cDate = cDate;
        this.orientador = orientador;
    }

    /**
     *
     * @return Tipo de Inestigador Efetivo (2)
     */
    @Override
    public int tipoInvest() {
        return 2;
    }

    /**
     *
     * @return Nome do orientador do Estudante.
     */
    public String getOrientador() {
        return orientador;
    }
    
    /**
     *
     * @return String para imprimir a informação do Estudante.
     */
    @Override
    public String toString() {
        return "Estudante -> Nome: " + getNome() + ", Email: " + getEmail() + ", Grupo: " + getGrupo() + ", Tese: "
                + tTese + ", Data de Tese: " + cDate + ", Orientador: " + orientador ;
    }
}
