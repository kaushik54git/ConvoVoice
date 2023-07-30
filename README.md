**ConvoVoice - Interactive Q&A Program**

## Introduction

ConvoVoice is an interactive question and answer (Q&A) program that allows users to engage in natural language conversations with the system. The program utilizes Azure Speech-to-Text (STT) and Text-to-Speech (TTS) services, along with FreeGPT, a Python library for answering questions using the power of GPT-based language models.

## Prerequisites

Before running ConvoVoice, ensure you have the following dependencies installed:

- Python 3.x
- Azure Cognitive Services (Speech-to-Text and Text-to-Speech) API credentials
- FreeGPT Python library (installation instructions can be found at https://github.com/Ruu3f/freeGPT)

## Setup

1. Clone this repository to your local machine or download the ZIP file and extract it.

2. Install the required Python libraries by running the following command in the project directory:

   ```
   pip install -r requirements.txt
   ```

3. Sign up for Azure Cognitive Services and obtain API credentials for Speech-to-Text and Text-to-Speech.

4. Create a `config.py` file in the project directory and add your Azure API credentials in the following format:

   ```python
   # config.py
   AZURE_SPEECH_KEY = 'YOUR_AZURE_SPEECH_API_KEY'
   AZURE_SPEECH_REGION = 'YOUR_AZURE_SPEECH_REGION'
   AZURE_TTS_KEY = 'YOUR_AZURE_TTS_API_KEY'
   AZURE_TTS_REGION = 'YOUR_AZURE_TTS_REGION'
   ```

## Usage

1. To start the ConvoVoice program, run the following command in the project directory:

   ```
   ./qanda.c
   ```

2. Once the program is running, you can ask questions or have conversations with ConvoVoice by speaking into your microphone.

3. ConvoVoice will use Azure Speech-to-Text to convert your speech into text, and then it will use FreeGPT to generate answers to your questions.

4. The program will use Azure Text-to-Speech to convert the answers back into spoken responses.

5. Enjoy your interactive Q&A session with ConvoVoice!

## Known Issues

- While the program uses state-of-the-art language models and services, it may occasionally provide inaccurate or unexpected responses. This is a limitation of current AI technology and is subject to improvement as newer models and services become available.

## Disclaimer

- ConvoVoice is a research project and should not be used as a substitute for professional advice or critical decision-making. The program's responses are generated based on statistical patterns in data and may not always be accurate or reliable.

## License

This project is licensed 

## Acknowledgments

- ConvoVoice makes use of the FreeGPT Python library, which is built upon GPT-based language models, a significant advancement in natural language processing.

- Thanks to Microsoft Azure for providing the Speech-to-Text and Text-to-Speech services, enabling ConvoVoice to understand and speak with users.

## Contact

If you have any questions, feedback, or suggestions, please feel free to reach out to us at kaushikkumbhat54@gmail.com
