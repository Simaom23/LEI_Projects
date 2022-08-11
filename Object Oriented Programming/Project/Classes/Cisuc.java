package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.util.ArrayList;
import java.time.Year;

/**
 * É classe que gere o programa.
 * Tem as listagens totais e contém as diferentes funções para calcular e apresentar listagens
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class Cisuc {

    private ArrayList<Grupo> gruposCisuc;
    private ArrayList<Publicacao> pubCisuc;
    private ArrayList<Investigador> membrosCisuc;

    /**
     * Construtor para a classe Cisuc.
     */
    public Cisuc() {
        this.gruposCisuc = new ArrayList<>();
        this.pubCisuc = new ArrayList<>();
        this.membrosCisuc = new ArrayList<>();
    }

    /**
     *
     * @return Lista de todos os Grupos gravados.
     */
    public ArrayList<Grupo> getGruposCisuc() {
        return gruposCisuc;
    }

    /**
     *
     * @return Lista de todas as Publicações gravadas.
     */
    public ArrayList<Publicacao> getPubCisuc() {
        return pubCisuc;
    }

    /**
     *
     * @return Lista de todos os Membros gravados.
     */
    public ArrayList<Investigador> getMembrosCisuc() {
        return membrosCisuc;
    }

    /**
     * Adiciona um novo grupo.
     *
     * @param newGrupo Grupo a adicionar
     */
    public void addGrupo(Grupo newGrupo) {
        gruposCisuc.add(newGrupo);
    }

    /**
     * Adiciona um novo investigador, caso ainda nao exista, ao seu grupo e à
     * lista de membros do CISUC.
     *
     * @param newInvest Objeto do tipo investigador.
     * @param flag Valor booleano que indica se está a ler de um ficheiro de
     * texto (true - sim, false - não).
     *
     */
    public void addMembro(Investigador newInvest, boolean flag) {
        if (flag) {
            for (Grupo searchGrupo : gruposCisuc) {
                if (searchGrupo.getAcronimo().toLowerCase().equals(newInvest.getGrupo().toLowerCase())) {
                    if (searchGrupo.getMembros().indexOf(newInvest) == -1) {
                        searchGrupo.newMembro(newInvest);
                    }
                }
            }
            if (membrosCisuc.indexOf(newInvest) == -1) {
                membrosCisuc.add(newInvest);
            }
        } else {
            if (membrosCisuc.indexOf(newInvest) == -1) {
                membrosCisuc.add(newInvest);
            }
        }
    }

    /**
     * Adiciona uma nova publicação, tanto à lista de publicações do CISUC como
     * verifica os autores e adiciona estas publicacões à lista de publicações
     * dos investigadores e dos grupos dos mesmos.
     *
     * @param pub Objeto do tipo Pubicacao.
     * @param flag Valor booleano que indica se está a ler de um ficheiro de
     * texto (true - sim, false - não).
     */
    public void addPub(Publicacao pub, boolean flag) {
        if (flag) {
            for (String autor : pub.getAutores()) {
                for (Grupo searchGrupo : gruposCisuc) {
                    for (Investigador searchInvestigador : searchGrupo.getMembros()) {
                        if (autor.substring(1, 1).equals(".") && searchInvestigador.getTipo() == 2) {
                            String[] tempSplit = searchInvestigador.getNome().split(" ");
                            String temp = tempSplit[1].substring(0, 0) + ". " + tempSplit[tempSplit.length - 1];
                            if (temp.equals(autor)) {
                                searchInvestigador.getPub().add(pub);
                                if (searchGrupo.getPub().indexOf(pub) == -1) {
                                    searchGrupo.getPub().add(pub);
                                }
                                break;
                            }
                        } else if (!(autor.substring(1, 1).equals(".")) && searchInvestigador.getTipo() == 1) {
                            String[] tempSplit = searchInvestigador.getNome().split(" ");
                            String temp = "Professor " + tempSplit[0] + " " + tempSplit[tempSplit.length - 1];
                            if (temp.equals(autor)) {
                                searchInvestigador.getPub().add(pub);
                                if (searchGrupo.getPub().indexOf(pub) == -1) {
                                    searchGrupo.getPub().add(pub);
                                }
                                break;
                            }
                        }
                    }
                }
            }
            if (pubCisuc.indexOf(pub) == -1) {
                pubCisuc.add(pub);
            }
        } else {
             if (pubCisuc.indexOf(pub) == -1) {
                pubCisuc.add(pub);
            }
        }
    }

    /**
     *
     * @return Tamanho da lista de membros do Cisuc
     */
    public int totalMembers() {
        return membrosCisuc.size();
    }

    /**
     * Calcula o número de Estudantes e Efetivos de cada grupo pertencente à
     * CISUC e devolve do número total de cada categoria de Investigador.
     *
     * @return Array contendo na primeira posição o total de efetivos e na
     * segunda posição o total de estudantes.
     *
     */
    public int[] totalCategory() {
        int[] categoriaInves = new int[2];
        for (Grupo searchGrupo : gruposCisuc) {
            categoriaInves[0] += searchGrupo.totalEfetivos();
            categoriaInves[1] += searchGrupo.totalEstudantes();
        }
        return categoriaInves;
    }

    /**
     * Calcula o número total de publicações do CISUC nos últimos 5 anos.
     *
     * @return Total de publicações nos últimos 5 anos.
     */
    public int pubFive() {
        int totalPub = 0;
        int anoAtual = Year.now().getValue();
        for (Grupo searchGrupo : gruposCisuc) {
            totalPub += searchGrupo.pubLastFive().size();
        }
        return totalPub;
    }

    /**
     * Calcula a quantidade de cada tipo de publicações percorrendo todos os
     * grupos.
     *
     *
     * @return Array contendo o tamanho de cada tipo de publicação nas 5
     * posições do mesmo.
     */
    public int[] pubCategory() {
        int[] categoriaPub = new int[5];
        for (Publicacao pub : pubCisuc) {
            if (pub.getTipo() == 1) {
                categoriaPub[0] += 1;
            } else if (pub.getTipo() == 2) {
                categoriaPub[1] += 1;
            } else if (pub.getTipo() == 3) {
                categoriaPub[2] += 1;
            } else if (pub.getTipo() == 4) {
                categoriaPub[3] += 1;
            } else if (pub.getTipo() == 5) {
                categoriaPub[4] += 1;
            }
        }
        return categoriaPub;
    }

    /**
     * Verifica se o grupo pedido existe, se existir cria uma lista com as
     * publicações dos últimos 5 anos desse grupo e devolve.
     *
     * @param acronimo
     * @return Lista contendo as publicações de um grupo nos últimos 5 anos e
     * null se o grupo nao existir.
     */
    public ArrayList<Publicacao> showPubGrupo(String acronimo) {
        ArrayList<Publicacao> lista = new ArrayList<>();
        int index = -1;
        for (Grupo searchGrupo : gruposCisuc) {
            if (searchGrupo.getAcronimo().toLowerCase().equals(acronimo.toLowerCase())) {
                lista = searchGrupo.getPub();
                index = gruposCisuc.indexOf(searchGrupo);
                break;
            }
        }
        if (index != -1) {
            int anoAtual = Year.now().getValue();
            for (Publicacao pub : lista) {
                if (pub.getAnoPub() < (anoAtual - 5)) {
                    lista.remove(lista.indexOf(pub));
                }
            }
            return lista;
        } else {
            System.out.printf("O grupo não existe.");
            return null;
        }
    }

    /**
     * Verifica se o grupo pedido existe, se existir cria uma lista com os
     * Investigadores desse grupo e devolve.
     *
     * @param acronimo
     * @return Lista contendo os investigadores de um grupo nos últimos 5 anos e
     * null se o grupo nao existir.
     */
    public ArrayList<Investigador> showInvesGrupo(String acronimo) {
        ArrayList<Investigador> lista = new ArrayList<>();
        int index = -1;
        for (Grupo searchGrupo : gruposCisuc) {
            if (searchGrupo.getAcronimo().toLowerCase().equals(acronimo.toLowerCase())) {
                lista = searchGrupo.getMembros();
                index = gruposCisuc.indexOf(searchGrupo);
                break;
            }
        }
        if (index != -1) {
            return lista;
        } else {
            System.out.printf("O grupo não existe.");
            return null;
        }
    }

    /**
     * Verifica se o Investigador pedido existe, se existir cria uma lista com
     * as publicações dos últimos 5 anos desse Investigador e devolve.
     *
     * @param nomeInvest
     * @return Lista contendo as publicações de um Investigador nos últimos 5
     * anos e null se o Investigador nao existir.
     */
    public ArrayList<Publicacao> showPubInvest(String nomeInvest) {
        ArrayList<Publicacao> lista = new ArrayList<>();
        int index = -1;
        for (Grupo searchGrupo : gruposCisuc) {
            for (Investigador searchInvest : searchGrupo.getMembros()) {
                if (searchInvest.getNome().toLowerCase().equals(nomeInvest.toLowerCase())) {
                    lista = searchInvest.getPub();
                    index = searchGrupo.getMembros().indexOf(searchInvest);
                    break;
                }
            }
        }
        if (index != -1) {
            return lista;
        } else {
            System.out.printf("O Investigador não existe.");
            return null;
        }
    }
}
