# -------------------------------------------------------------------------
# Projeto: Análise Exploratória de Dados - Saúde da Mulher (Climatério)
# Objetivo: Limpeza de dados, tratamento de valores ausentes (NAs) 
#           e cálculo de medidas de tendência central.
# -------------------------------------------------------------------------

# 1. Carregamento de Bibliotecas e Dados
# library(Rcmdr) # Interface gráfica utilizada para exploração inicial
# View(Climaterio)

# 2. Tratamento de Dados Ausentes (Data Cleaning)
# Verificando se há valores NA na coluna IDADE para evitar erros nos cálculos
coluna_idade <- Climaterio$IDADE
missing_idade <- which(is.na(coluna_idade))
print(paste("Índices com NA na Idade:", missing_idade))

# 3. Análise da Variável: IDADE
mean_idade <- mean(coluna_idade, na.rm = TRUE)
median_idade <- median(coluna_idade, na.rm = TRUE)
summary_idade <- summary(coluna_idade)

# Cálculo da Moda (Função customizada para análise de frequência)
moda_idade <- names(which.max(table(coluna_idade)))
print(paste("Média:", mean_idade, "| Mediana:", median_idade, "| Moda:", moda_idade))

# 4. Análise Multivariada (Peso, Altura, IMC, Renda)
# Resumo estatístico completo para identificar outliers e dispersão
summary(Climaterio[, c("Peso", "Altura", "IMC", "Renda")])

# 5. Análise de Saúde Reprodutiva e Cardiovascular
# Medidas para Menarca, Menopausa e Pressão Arterial Sistólica
summary(Climaterio$PA.sistólica)
moda_PAsistolica <- names(which.max(table(Climaterio$PA.sistólica)))

# 6. Manipulação de Matrizes (Exemplo de Álgebra Linear aplicada)
# Demonstração de seleção de elementos em matrizes 3x3
A <- matrix(c(1,2,3,4,5,6,7,8,9), nrow=3, ncol=3, byrow=TRUE)
primeira_coluna <- A[ ,1]
primeira_linha <- A[1, ]
