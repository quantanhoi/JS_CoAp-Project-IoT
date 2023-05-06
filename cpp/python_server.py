import asyncio
from aiocoap import Context, Message, resource, Code


class HelloWorldResource(resource.Resource):
    async def render_post(self, request):
        payload = request.payload.decode('utf-8')
        print(f'Received message from client: {payload}')
        
        response = Message(code=Code.CONTENT)
        response.payload = payload.encode('utf-8')
        response.opt.content_format = 0  # Set Content-Format to text/plain
        return response

async def main():
    root = resource.Site()
    root.add_resource(('hello',), HelloWorldResource())

    context = await Context.create_server_context(root, bind=("localhost", 5683))

    print("CoAP server is up and running. Press Ctrl+C to exit.")
    await asyncio.get_event_loop().create_future()

if __name__ == "__main__":
    try:
        asyncio.get_event_loop().run_until_complete(main())
    except KeyboardInterrupt:
        print("\nServer stopped.")

