package projetopoo;

/**
 *
 * @author Simão Monteiro Nº12019215412
 * @version 1.0
 */
import java.util.ArrayList;
import java.io.*;
import java.time.Year;

/**
 * Define os diferentes grupos do CISUC.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class Grupo implements Serializable {

    private String nome;
    private String acronimo;
    private String iResponsavel;
    private ArrayList<Investigador> membros;
    private ArrayList<Publicacao> pub;

    /**
     * Construtor da classe Grupo.
     * @param nome Nome do Grupo.
     * @param acronimo Acrónimo do Grupo.
     * @param iResponsavel Nome do Investigador Responsável.
     */
    public Grupo(String nome, String acronimo, String iResponsavel) {
        this.nome = nome;
        this.acronimo = acronimo;
        this.iResponsavel = iResponsavel;
        this.membros = new ArrayList<>();
        this.pub = new ArrayList<>();
    }

    /**
     *
     * @return Lista dos membros do Grupo.
     */
    public ArrayList<Investigador> getMembros() {
        return membros;
    }

    /**
     *
     * @return Lista das publicações do Grupo.
     */
    public ArrayList<Publicacao> getPub() {
        return pub;
    }

    /**
     *
     * @return Acronimo do grupo.
     */
    public String getAcronimo() {
        return acronimo;
    }
    
    /**
     * 
     * @return Nome do Investigador responsável do Grupo.
    */
    public String getiResponsavel() {
        return iResponsavel;
    }
    
    

    /**
     * Adiciona o investigador ao grupo.
     * Se o investigador for do tipo estudante verifica se o seu orientador pertence ao grupo se não pertencer
     * não adiciona e envia uma mensagem de erro.
     * @param newInvest Objeto Investigador a adicionar ao grupo.
     */
    public void newMembro(Investigador newInvest) {
        if (newInvest.getTipo() == 2) {
            Estudante newEstudante = (Estudante) newInvest;
            boolean flag = false;
            for (Investigador searchMembros : membros) {
                if (searchMembros.getTipo() == 1) {
                    if (searchMembros.getNome().toLowerCase().equals(newEstudante.getOrientador().toLowerCase())) {
                        membros.add(newEstudante);
                        flag = true;
                        break;
                    }
                }
            }
            if(!flag){
                System.out.printf("O orientador do Investigador %s não pertence ao Grupo.\n", newEstudante.getNome());
            }
        } else {
            membros.add(newInvest);
        }
    }
    /**
     * Calcula a quantidade de efetivos do grupo.
     * @return Total de efetivos.
     */
    public int totalEfetivos() {
        int totalEfetivos = 0;
        for (Investigador total : membros) {
            if (total.getTipo() == 1) {
                totalEfetivos += 1;
            }
        }
        return totalEfetivos;
    }

    /**
     * Calcula a quntidade de estudantes do grupo.
     * @return Total de estudantes.
     */
    public int totalEstudantes() {
        int totalEstudantes = 0;
        for (Investigador total : membros) {
            if (total.getTipo() == 2) {
                totalEstudantes += 1;
            }
        }
        return totalEstudantes;
    }

    /**
     * Cria uma lista com as publicações dos últimos 5 anos do grupo e devolve.
     * @return Lista dos últimos 5 anos do Grupo.
     */
    public ArrayList<Publicacao> pubLastFive() {
        ArrayList<Publicacao> lastFive = new ArrayList<>();
        int anoAtual = Year.now().getValue();
        for (Publicacao count : pub) {
            if (count.getAnoPub() >= (anoAtual - 5)) {
                lastFive.add(count);
            }
        }
        return lastFive;
    }

    /**
     *
     * @return String para imprimir conteúdos do Grupo.
     */
    @Override
    public String toString() {
        return acronimo + " - " + nome + " - " + "Responsável: " + iResponsavel;
    }

}
