import asyncio
import keyboard
from aiocoap import Context, Message
from aiocoap.numbers.codes import Code

async def send_key_press(context, key):
    request = Message(code=Code.POST, payload=key.encode('utf-8'), uri="coap://127.0.0.1/myresource")
    response = await context.request(request).response
    print(f"POST response: {response.payload.decode('utf-8')}")

async def main():
    context = await Context.create_client_context()

    # Send a GET request to the server (optional)
    # ...

    # Send a PUT request to update the resource (optional)
    # ...

    # Send another GET request to see the updated content (optional)
    # ...

    print("Press any key to send a request to the server. Press 'q' to exit.")

    while True:
        event = keyboard.read_event(True)
        if event.event_type == keyboard.KEY_DOWN:
            if event.name == 'q':
                break
            if event.name is not None:
                await send_key_press(context, event.name)

if __name__ == "__main__":
    asyncio.run(main())
