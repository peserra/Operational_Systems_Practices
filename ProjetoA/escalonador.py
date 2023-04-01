import time
import threading


# filas implementadas com lista para facilitar a ordenação dos processos
queue_0 = []
queue_1 = []
queue_2 = []
queue_3 = []


class Process:
    def __init__(self, nome, prioridade, cpu_burst):
        self.nome = nome
        self.prioridade = prioridade
        self.cpu_burst = cpu_burst

    # como objeto será representado num print
    def __repr__(self) -> str:
        return f"Nome: {self.nome}, Prioridade Original: {self.prioridade}, Cpu Burst: {self.cpu_burst}"


def posiciona_na_fila(objeto_processo: Process):
    prioridade = objeto_processo.prioridade

    if prioridade == 0:
        queue_0.append(processo)
    elif prioridade == 1:
        queue_1.append(processo)
    elif prioridade == 2:
        queue_2.append(processo)
    elif prioridade == 3:
        queue_3.append(processo)

# a cada 10 unidades de tempo, aumenta prioridade do ultimo elemento na fila (muda ele de fila)


def aging():
    filas = [queue_3, queue_2, queue_1, queue_0]
    for fila in filas:
        if fila != queue_0:
            if not fila:
                continue
            
            ultimo_elemento = fila.pop(-1)  # pega ultimo elemento da fila
            
            index_atual = filas.index(fila) # pega o index atual da lista de filas
            
            filas[index_atual + 1].append(ultimo_elemento) # adiciona o elemento no final da proxima fila na lista de filas
            fila.sort(key=lambda x: x.cpu_burst)
    
    


def seleciona_fila() -> list:
    filas = [queue_0, queue_1, queue_2, queue_3]
    for fila in filas:
        if not fila:  # se fila está vazia
            continue
        return fila
    return None  # todas as filas estão vazias -> fim da execução



def escalonador():
    # tenho que escalonar os processos que ganham o processador
    # prioridade: fila 0 > fila 1 > fila 2 > fila 3
    # só "rodo" fila n, se fila n-1 está vazia
    try:
        while (seleciona_fila != None):
            fila_executada = seleciona_fila()
            fila_executada.sort(key=lambda x: x.cpu_burst)  # desempate SJB
            processo_executando = fila_executada.pop(0)
            print(f"Começando execução do processo '{processo_executando}'")
            threading.Timer(1, aging())             # uma thread separada executa a função de aging
            inicio = time.time()                    # executa função aging a cada 1s
            time.sleep(processo_executando.cpu_burst/10)    # simula processo sendo executado, cpu_burst dividido por 10 pra ser mais rapido
            fim = time.time()
            print(f"Terminando execução de '{processo_executando.nome}' \ntempo de execução: {(fim - inicio):.2f} segundos (cpu burst / 10)")
            print("--------------------------------------------------------------------------------------")
    except:
        print("fim da execução")


# programa pega input de um arquivo do tipo txt como entrada, não cole direto no terminal
if __name__ == "__main__":
    print("")
    # ETAPA 1, AQUISIÇÃO DE DADOS
    path = input(
        'Cole o caminho do arquivo txt contendo lista de entradas sem aspas, por favor\n')
    print("")
    print("--------------------------------------------------------------------------------------")
    with open(path) as file:
        for line in file:
            line = line.strip()
            line_as_array = line.split(',')
            nome = line_as_array[0]
            prioridade = int(line_as_array[1])
            cpu_burst = int(line_as_array[2])
            processo = Process(nome, prioridade, cpu_burst)
            posiciona_na_fila(processo)
    # ETAPA 2, ESCALONAR PROCESSOS
    escalonador()
    print("--------------------------------------------------------------------------------------")
    