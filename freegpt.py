import freeGPT
from asyncio import run


async def main():
    while True:
        print("\n")
        prompt = input("enter your prompt ")
        try:
            resp = await getattr(freeGPT, "gpt4").Completion.create(prompt)
            print(resp)
        except Exception as e:
            print(f"🤖: {e}")


run(main())